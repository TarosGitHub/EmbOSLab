#include "defines.h"
#include "kozos.h"
#include "intr.h"
#include "interrupt.h"
#include "syscall.h"
#include "lib.h"

#define THREAD_NUM 6
#define THREAD_NAME_SIZE 15

/**
 * @brief スレッドのコンテキスト
 */
typedef struct _kz_context {
    uint32 sp; /* スタックポインタ */
} kz_context;

/**
 * @brief タスク・コントロール・ブロック(TCB)
 */
typedef struct _kz_thread {
    struct _kz_thread* next; /* レディーキューへの接続に使用するポインタ */
    char name[THREAD_NAME_SIZE + 1]; /* スレッド名 */
    char* stack; /* スタック */

    /* スレッドのスタートアップ(thread_init)に渡すパラメータ */
    struct {
        kz_func_t func; /* スレッドのメイン関数 */
        int argc; /* スレッドのメイン関数のargc */
        char** argv; /* スレッドのメイン関数のargv */
    } init;

    /* システムコール用バッファ */
    struct {
        kz_syscall_type_t type;
        kz_syscall_param_t* param;
    } syscall;

    kz_context context; /* コンテキスト情報 */
} kz_thread;

/**
 * @brief レディーキュー
 */
static struct {
    kz_thread* head;
    kz_thread* tail;
} readyque;

static kz_thread* current; /* 現在実行中のスレッド */
static kz_thread threads[THREAD_NUM]; /* 各スレッド(タスク・コントロール・ブロックの実体) */
static kz_handler_t handlers[SOFTVEC_TYPE_NUM]; /* 各割込みハンドラ */

/**
 * @brief スレッドのディスパッチを行う.
 *
 * @param context スレッドのコンテキスト
 * @see startup.s
 */
extern void dispatch(kz_context* context);

/**
 * @brief レディーキューからカレントスレッドを抜き出す.
 *
 * @return currentがNULLの場合、-1. それ以外の場合、0.
 */
static int getcurrent(void)
{
    if (current == NULL) {
        return -1;
    }

    readyque.head = current->next;
    if (readyque.head == NULL) {
        readyque.tail = NULL;
    }
    current->next = NULL;

    return 0;
}

/**
 * @brief カレントスレッドをレディーキューに繋げる
 *
 * @return currentがNULLの場合、-1. それ以外の場合、0.
 */
static int putcurrent(void)
{
    if (current == NULL) {
        return -1;
    }

    if (readyque.tail) {
        readyque.tail->next = current;
    }
    else {
        readyque.head = current;
    }
    readyque.tail = current;

    return 0;
}

/**
 * @brief スレッドを終了する.
 */
static void thread_end(void)
{
    kz_exit();
}

/**
 * @brief スレッドのスタートアップ.
 *
 * @param thp スレッド
 */
static void thread_init(kz_thread* thp)
{
    thp->init.func(thp->init.argc, thp->init.argv);
    thread_end();
}

/**
 * @brief システムコールの処理(kz_run():スレッドの起動)
 *
 * @param func スレッド上で実行される関数(メイン関数)
 * @param name スレッド名
 * @param stacksize 確保するスタックサイズ
 * @param argc メイン関数の引数の数
 * @param argv メイン関数に渡す引数
 * @return 以下の場合は、-1. それ以外の場合は、スレッドID を返す.
 *         - 空いているタスク・コントロール・ブロックが見つからなかった
 */
static kz_thread_id_t thread_run(kz_func_t func, char* name, int stacksize, int argc, char* argv[])
{
    int i;
    kz_thread* thp;
    uint32* sp;
    extern char userstack;
    static char* thread_stack = &userstack;

    /* 空いているタスク・コントロール・ブロックを検索 */
    for (i = 0; i < THREAD_NUM; i++) {
        thp = &threads[i];
        if (!thp->init.func) {
            /* 見つかった */
            break;
        }
    }
    if (i == THREAD_NUM) {
        return -1;
    }

    memset(thp, 0, sizeof(*thp));

    /* タスク・コントロール・ブロックの設定 */
    strcpy(thp->name, name);
    thp->next = NULL;
    thp->init.func = func;
    thp->init.argc = argc;
    thp->init.argv = argv;

    /* スタック領域を獲得 */
    memset(thread_stack, 0, stacksize);
    thread_stack += stacksize;

    thp->stack = thread_stack;

    /* スタックの設定 */
    sp = (uint32)thp->stack;
    *(--sp) = (uint32)thread_end; /* thread_init()からの戻り先 */
    *(--sp) = (uint32)thread_init; /* ディスパッチ時にプログラムカウンタに設定される */
    *(--sp) = 0;
    *(--sp) = 0;
    *(--sp) = 0;
    *(--sp) = 0;
    *(--sp) = 0;
    *(--sp) = 0;
    *(--sp) = (uint32)thp; /* thread_init()に渡す 第1引数 */

    thp->context.sp = (uint32)sp;

    /* システムコールを呼び出したスレッドをレディーキューに戻す */
    putcurrent();

    /* 新規作成したスレッドをレディーキューに接続する */
    current = thp;
    putcurrent();

    return (kz_thread_id_t)current;
}

/**
 * @brief システムコールの処理(kz_exit():スレッドの終了)
 *        スレッド時の終了メッセージを表示し、タスク・コントロール・ブロックを初期化する.
 *
 * @return 常に0を返す.
 */
static int thread_exit(void)
{
    puts(current->name);
    puts(" EXIT.\n");
    memset(current, 0, sizeof(*current));

    return 0;
}

/**
 * @brief 割込みハンドラの登録.
 *
 * @param type ソフトウェア・割込みベクタ種別
 * @param handler 割込みハンドラ
 * @return 常に0を返す.
 */
static int setintr(softvec_type_t type, kz_handler_t handler)
{
    static void thread_intr(softvec_type_t type, unsigned long sp);

    softvec_setintr(type, thread_intr);
    handlers[type] = handler;

    return 0;
}

/**
 * @brief システムコールを呼び出す.
 *
 * @param type システム・コール番号
 * @param p システム・コール呼び出し時のパラメータ
 */
static void call_functions(kz_syscall_type_t type, kz_syscall_param_t* p)
{
    switch (type) {
    case KZ_SYSCALL_TYPE_RUN:
        p->un.run.ret = thread_run(p->un.run.func, p->un.run.name, p->un.run.stacksize, p->un.run.argc, p->un.run.argv);
        break;

    case KZ_SYSCALL_TYPE_EXIT:
        thread_exit();
        break;

    default:
        break;
    }
}

/**
 * @brief システムコールの処理
 *
 * @param type システム・コール番号
 * @param p システム・コール呼び出し時のパラメータ
 */
static void syscall_proc(kz_syscall_type_t type, kz_syscall_param_t* p)
{
    getcurrent();
    call_functions(type, p);
}

/**
 * @brief スレッドのスケジューリング
 *        ラウンドロビン方式.
 *        レディーキューにスレッドが登録されていなければ停止する.
 */
static void schedule(void)
{
    if (!readyque.head) {
        kz_sysdown();
    }

    current = readyque.head;
}

/**
 * @brief システムコールの呼び出し
 */
static void syscall_intr(void)
{
    syscall_proc(current->syscall.type, current->syscall.param);
}

/**
 * @brief ソフトウェアエラーの処理
 */
static void softerr_intr(void)
{
    puts(current->name);
    puts(" DOWN.\n");
    getcurrent();
    thread_exit();
}

/**
 * @brief 割込み処理の入り口.
 *
 * @param type ソフトウェア・割込みベクタ種別
 * @param sp スタックポインタ
 */
static void thread_intr(softvec_type_t type, unsigned long sp)
{
    current->context.sp = sp;

    if (handlers[type]) {
        handlers[type]();
    }

    schedule();

    dispatch(&current->context);
}

void kz_start(kz_func_t func, char* name, int stacksize, int argc, char* argv[])
{
    current = NULL;

    readyque.head = NULL;
    readyque.tail = NULL;
    memset(threads, 0, sizeof(threads));
    memset(handlers, 0, sizeof(handlers));

    setintr(SOFTVEC_TYPE_SYSCALL, syscall_intr);
    setintr(SOFTVEC_TYPE_SOFTERR, softerr_intr);

    current = (kz_thread*)thread_run(func, name, stacksize, argc, argv);

    /* 最初のスレッドをディスパッチによって起動 */
    dispatch(&current->context);

    /* ここには返ってこない */
}

void kz_sysdown(void)
{
    puts("system error!\n");
    while (1) {
        /* DO NOTHING */
    }
}

void kz_syscall(kz_syscall_type_t type, kz_syscall_param_t* param)
{
    current->syscall.type = type;
    current->syscall.param = param;
    asm volatile ("trapa #0");
}
