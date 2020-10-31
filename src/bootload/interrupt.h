#ifndef INTERRUPT_H_INCLUDED
#define INTERRUPT_H_INCLUDED

extern char softvec;
#define SOFTVEC_ADDR (&softvec)

/**
 * @brief ソフトウェア・割込みベクタ種別型.
 */
typedef short softvec_type_t;

/**
 * @brief ソフトウェア・割込みハンドラ型.
 *
 * @param type ソフトウェア・割込みベクタ種別
 * @param sp スタックポインタ
 */
typedef void (* softvec_handler_t)(softvec_type_t type, unsigned long sp);

/**
 * @brief ソフトウェア・割込みベクタテーブル.
 */
#define SOFTVECS ((softvec_handler_t*)SOFTVEC_ADDR)

/**
 * @brief 割込み有効化.
 */
#define INTR_ENABLE() asm volatile ("andc.b #0x3f, ccr")

/**
 * @brief 割込み無効化(割込み禁止).
 */
#define INTR_DISABLE() asm volatile ("orc.b #0xc0, ccr")

/**
 * @brief ソフトウェア・割込みベクタ初期化.
 * 
 * @return 常に0を返す.
 */
extern int softvec_init(void);

/**
 * @brief ソフトウェア・割込みハンドラ設定.
 * 
 * @param type ソフトウェア・割込みベクタ種別
 * @param handler ソフトウェア・割込みハンドラ
 * @return 常に0を返す.
 */
extern int softvec_setintr(softvec_type_t type, softvec_handler_t handler);

/**
 * @brief 共通割込みハンドラ.
 * 
 * @param type ソフトウェア・割込みベクタ種別
 * @param sp スタックポインタ
 */
extern void interrupt(softvec_type_t type, unsigned long sp);

#endif
