#include "defines.h"

extern void start(void);
extern void intr_softerr(void);
extern void intr_syscall(void);
extern void intr_serintr(void);

/*
 * 割込みベクタの設定.
 * リンカ・スクリプトの定義により、先頭番地に配置される.
 */
void (* vectors[])(void) = {
           /* 割込み要因  番号  アドレス */
    start, /* リセット   0  H'0000～H'0003 */
    NULL, /* reserved   1  H'0004～H'0007 */
    NULL, /* reserved   2  H'0008～H'000B */
    NULL, /* reserved   3  H'000C～H'000F */
    NULL, /* reserved   4  H'0010～H'0013 */
    NULL, /* reserved   5  H'0014～H'0017 */
    NULL, /* reserved   6  H'0018～H'001B */
    NULL, /* NMI   7  H'001C～H'001F */
    intr_syscall, /* トラップ命令   8  H'0020～H'0023 */
    intr_softerr, /* トラップ命令   9  H'0024～H'0027 */
    intr_softerr, /* トラップ命令  10  H'0028～H'002B */
    intr_softerr, /* トラップ命令  11  H'002C～H'002F */
    NULL, /* 外部割り込みIRQ0  12  H'0030～H'0033 */
    NULL, /* 外部割り込みIRQ1  13  H'0034～H'0037 */
    NULL, /* 外部割り込みIRQ2  14  H'0038～H'003B */
    NULL, /* 外部割り込みIRQ3  15  H'003C～H'003F */
    NULL, /* 外部割り込みIRQ4  16  H'0040～H'0043 */
    NULL, /* 外部割り込みIRQ5  17  H'0044～H'0047 */
    NULL, /* reserved  18  H'0048～H'004B */
    NULL, /* reserved  19  H'004C～H'004F */
    NULL, /* ウォッチドッグタイマ WOVI（インターバルタイマ）  20  H'0050～H'0053 */
    NULL, /* DRAMインターフェース CMI（コンペアマッチ）  21  H'0054～H'0057 */
    NULL, /* reserved  22  H'0058～H'005B */
    NULL, /* A/D ADI（A/D エンド）  23  H'005C～H'005F */
    NULL, /* 16ビットタイマチャネル0 IMIA0（コンペアマッチ／インプットキャプチャ A0）  24  H'0060～H'0063 */
    NULL, /* 16ビットタイマチャネル0 IMIB0（コンペアマッチ／インプットキャプチャ B0）  25  H'0064～H'0067 */
    NULL, /* 16ビットタイマチャネル0 OVI0 （オーバフロー0）  26  H'0068～H'006B */
    NULL, /* reserved  27  H'006C～H'006F */
    NULL, /* 16ビットタイマチャネル1 IMIA1（コンペアマッチ／インプットキャプチャ A1）  28  H'0070～H'0073 */
    NULL, /* 16ビットタイマチャネル1 IMIB1（コンペアマッチ／インプットキャプチャ B1）  29  H'0074～H'0077 */
    NULL, /* 16ビットタイマチャネル1 OVI1（オーバフロー1） 30  H'0078～H'007B */
    NULL, /* reserved  31  H'007C～H'007F */
    NULL, /* 16ビットタイマチャネル2 IMIA2（コンペアマッチ／インプットキャプチャ A2）  32  H'0080～H'0083 */
    NULL, /* 16ビットタイマチャネル2 IMIB2（コンペアマッチ／インプットキャプチャ B2）  33  H'0084～H'0087 */
    NULL, /* 16ビットタイマチャネル2 OVI2（オーバフロー2）  34  H'0088～H'008B */
    NULL, /* reserved  35  H'008C～H'008F */
    NULL, /* 8ビットタイマチャネル0/1 CMIA0（コンペアマッチA0）  36  H'0090～H'0093 */
    NULL, /* 8ビットタイマチャネル0/1 CMIB0（コンペアマッチB0）  37  H'0094～H'0097 */
    NULL, /* 8ビットタイマチャネル0/1 CMIA1/CMIB1（コンペアマッチA1/B1）  38  H'0098～H'009B */
    NULL, /* 8ビットタイマチャネル0/1 TOVI0/TOVI1（オーバフロー0/1）  39  H'009C～H'009F */
    NULL, /* 8ビットタイマチャネル2/3 CMIA2（コンペアマッチA2）  40  H'00A0～H'00A3 */
    NULL, /* 8ビットタイマチャネル2/3 CMIB2（コンペアマッチB2）  41  H'00A4～H'00A7 */
    NULL, /* 8ビットタイマチャネル2/3 CMIA3/CMIB3（コンペアマッチA3/B3）  42  H'00A8～H'00AB */
    NULL, /* 8ビットタイマチャネル2/3 TOVI2/TOVI3（オーバフロー2/3）  43  H'00AC～H'00AF */
    NULL, /* DMAC DEND0A  44  H'00B0～H'00B3 */
    NULL, /* DMAC DEND0B  45  H'00B4～H'00B7 */
    NULL, /* DMAC DEND1A  46  H'00B8～H'00BB */
    NULL, /* DMAC DEND1B  47  H'00BC～H'00BF */
    NULL, /* reserved  48  H'00C0～H'00C3 */
    NULL, /* reserved  49  H'00C4～H'00C7 */
    NULL, /* reserved  50  H'00C8～H'00CB */
    NULL, /* reserved  51  H'00CC～H'00CF */
    intr_serintr, /* SCIチャネル0 ERI0（受信エラー0）  52  H'00D0～H'00D3 */
    intr_serintr, /* SCIチャネル0 RXI0（受信完了0）  53  H'00D4～H'00D7 */
    intr_serintr, /* SCIチャネル0 TXI0（送信データエンプティ0）  54  H'00D8～H'00DB */
    intr_serintr, /* SCIチャネル0 TEI0（送信終了0）  55  H'00DC～H'00DF */
    intr_serintr, /* SCIチャネル1 ERI1（受信エラー1）  56  H'00E0～H'00E3 */
    intr_serintr, /* SCIチャネル1 RXI1（受信完了1）  57  H'00E4～H'00E7 */
    intr_serintr, /* SCIチャネル1 TXI1（送信データエンプティ1）  58  H'00E8～H'00EB */
    intr_serintr, /* SCIチャネル1 TEI1（送信終了1）  59  H'00EC～H'00EF */
    intr_serintr, /* SCIチャネル2 ERI2（受信エラー2）  60  H'00F0～H'00F3 */
    intr_serintr, /* SCIチャネル2 RXI2（受信完了2）  61  H'00F4～H'00F7 */
    intr_serintr, /* SCIチャネル2 TXI2（送信データエンプティ2）  62  H'00F8～H'00FB */
    intr_serintr  /* SCIチャネル2 TEI2（送信終了2）  63  H'00FC～H'00FF */
};
