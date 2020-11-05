#ifndef KOZOS_DEFINES_H_INCLUDED
#define KOZOS_DEFINES_H_INCLUDED

#include "defines.h"

/**
 * @brief スレッドID型
 */
typedef uint32 kz_thread_id_t;

/**
 * @brief スレッド上で実行される関数の型
 */
typedef int (* kz_func_t)(int argc, char* argv[]);

/**
 * @brief 割込みハンドラ型
 */
typedef void (* kz_handler_t)(void);

#endif
