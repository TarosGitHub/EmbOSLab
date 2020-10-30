#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

/**
 * @brief SCIを初期化する.
 *        送信動作と受信動作を許可する. また、BRR を64に設定する.
 *        また、SSR.TEND と SSR.TDRE を0に設定する。
 * 
 * @param index SCIチャネル番号
 * @return 常に0を返す.
 */
extern int serial_init(int index);

/**
 * @brief 送信可能かどうか判断する.
 * 
 * @param index SCIチャネル番号
 * @return 送信可能の場合は1. そうでない場合は0を返す.
 */
extern int serial_is_send_enable(int index);

/**
 * @brief 1文字を送信する.
 * 
 * @param index SCIチャネル番号
 * @param c 送信する文字
 * @return 常に0を返す.
 */
extern int serial_send_byte(int index, unsigned char c);

/**
 * @brief 受信可能かどうか判断する.
 * 
 * @param index SCIチャネル番号
 * @return 受信可能の場合は1. そうでない場合は0を返す.
 */
extern int serial_is_recv_enable(int index);

/**
 * @brief 1文字を受信する.
 * 
 * @param index SCIチャネル番号
 * @return 受信した文字.
 */
extern unsigned char serial_recv_byte(int index);

#endif
