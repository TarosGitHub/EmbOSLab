#ifndef KOZOS_H_INCLUDED
#define KOZOS_H_INCLUDED

#include "kozos_defines.h"
#include "syscall.h"

/**
 * @brief 初期スレッドを生成し、メイン関数の実行を開始する.
 *        初期スレッドはすべてのスレッドの親スレッド. 当スレッド上で kz_run() を使用し、子スレッドを生成する.
 *        初期スレッド生成後はそのスレッドの動作に入り、この関数から戻ることはない.
 *
 * @param func メイン関数
 * @param name スレッド名
 * @param stacksize スタックサイズ
 * @param argc メイン関数に渡す引数の個数
 * @param argv メイン関数に渡す引数
 */
extern void kz_start(kz_func_t func, char* name, int stacksize, int argc, char* argv[]);

/**
 * @brief メッセージを出力し、停止する.
 */
extern void kz_sysdown(void);

/**
 * @brief システム・コールを実行する.
 *
 * @param type システム・コール番号
 * @param param システム・コール呼び出し時のパラメータ
 */
extern void kz_syscall(kz_syscall_type_t type, kz_syscall_param_t* param);

extern int test08_1_main(int argc, char* argv[]);

#endif
