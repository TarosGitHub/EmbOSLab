#ifndef KOZOS_SYSCALL_H_INCLUDED
#define KOZOS_SYSCALL_H_INCLUDED

#include "kozos_defines.h"

/**
 * @brief システム・コール番号
 */
typedef enum {
    KZ_SYSCALL_TYPE_RUN = 0,
    KZ_SYSCALL_TYPE_EXIT
} kz_syscall_type_t;

/**
 * @brief システム・コール呼び出し時のパラメータ
 */
typedef struct {
    union {
        /* kz_run() のパラメータ */
        struct {
            kz_func_t func; /* メイン関数 */
            char* name; /* スレッド名 */
            int stacksize; /* スタックサイズ */
            int argc; /* メイン関数に渡す引数の個数 */
            char** argv; /* メイン関数に渡す引数 */
            kz_thread_id_t ret; /* kz_run() の戻り値 */
        } run;

        /* kz_exit() のパラメータ */
        struct {
            int dummy; /* 引数なし */
        } exit;
    } un;
} kz_syscall_param_t;

/**
 * @brief スレッドを生成し、スレッド上でメイン関数の実行を開始する.
 *
 * @param func メイン関数
 * @param name スレッド名
 * @param stacksize スタックサイズ
 * @param argc メイン関数に渡す引数の個数
 * @param argv メイン関数に渡す引数
 * @return 生成したスレッドのID.
 */
extern kz_thread_id_t kz_run(kz_func_t func, char* name, int stacksize, int argc, char* argv[]);

/**
 * @brief スレッドを終了する.
 */
extern void kz_exit(void);

#endif
