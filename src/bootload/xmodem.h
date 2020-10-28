#ifndef XMODEM_H_INCLUDED
#define XMODEM_H_INCLUDED

/**
 * @brief XMODEMによるデータ受信.
 *
 * @param buf 受信データバッファへのポインタ
 * @return 受信エラー時は-1. それ以外は受信データサイズ(Byte)
 */
extern long xmodem_recv(char* buf);

# endif
