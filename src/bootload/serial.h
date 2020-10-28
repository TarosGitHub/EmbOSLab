#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

/* デバイス初期化 */
extern int serial_init(int index);

/* 送信可能か？ */
extern int serial_is_send_enable(int index);

/* 1文字送信 */
extern int serial_send_byte(int index, unsigned char c);

/* 受信可能か？ */
extern int serial_is_recv_enable(int index);

/* 1文字受信 */
extern unsigned char serial_recv_byte(int index);

#endif
