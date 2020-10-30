#include "defines.h"

/* スタート・アップ */
extern void start(void);

/*
 * 割込みベクタの設定.
 * リンカ・スクリプトの定義により、先頭番地に配置される.
 */
void (* vectors[])(void) = {
           /* 割込み要因  番号  アドレス */
    start, /* リセット   0     H'0000～H'0003 */
    NULL, /* reserved   1  H'0004～H'0007 */
    NULL, /* reserved   2  H'0008～H'000B */
    NULL, /* reserved   3  H'000C～H'000F */
    NULL, /* reserved   4  H'0010～H'0013 */
    NULL, /* reserved   5  H'0014～H'0017 */
    NULL, /* reserved   6  H'0018～H'001B */
    NULL, /* NMI   7  H'001C～H'001F */
    NULL, /* トラップ命令   8  H'0020～H'0023 */
    NULL, /* トラップ命令   9  H'0024～H'0027 */
    NULL, /* トラップ命令  10  H'0028～H'002B */
    NULL, /* トラップ命令  11  H'002C～H'002F */
    NULL, /* 外部割り込みIRQ0  12  H'0030～H'0033 */
    NULL, /* 外部割り込みIRQ1  13  H'0034～H'0037 */
    NULL, /* 外部割り込みIRQ2  14  H'0038～H'003B */
    NULL, /* 外部割り込みIRQ3  15  H'003C～H'003F */
    NULL, /* 外部割り込みIRQ4  16  H'0040～H'0043 */
    NULL, /* 外部割り込みIRQ5  17  H'0044～H'0047 */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL, /*  */
    NULL  /*  */
};
