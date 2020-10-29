#include "defines.h"
#include "serial.h"
#include "xmodem.h"
#include "elf.h"
#include "lib.h"

static int init(void)
{
    extern int erodata, data_start, erodata, edata, bss_start, ebss;

    /* データセクションの内容を ROM から RAM へコピーする */
    memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);

    /* BSS領域を0に初期化する */
    memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

    /* SCIの初期化 */
    serial_init(SERIAL_DEFAULT_DEVICE);

    return 0;
}

/* メモリの16進数ダンプ */
static int dump(char* buf, long size)
{
    long i;

    if (size < 0) {
        puts("no data.\n");
        return -1;
    }

    for (i = 0; i < size; i++) {
        putxval(buf[i], 2);

        if ((i & 0xf) == 15) {
            puts("\n");
        }
        else {
            if ((i & 0xf) == 7) {
                puts(" ");
            }
            puts(" ");
        }
    }
    puts("\n");

    return 0;
}

static void wait()
{
    volatile long i;
    
    for (i = 0; i < 300000; i++) {
        /* NO NOTHING */
    }
}

int main(void)
{
    static char command[16];
    static long size = -1;
    static unsigned char* loadbuf = NULL;
    extern int buffer_start;

    init();

    puts("kzload (kozos boot loader) started.\n");

    while (1) {
        /* コマンド受付 */
        puts("kzload> ");
        gets(command);

        if (!strcmp(command, "load")) {
            /* load コマンド実行 */
            loadbuf = (char*)(&buffer_start);
            size = xmodem_recv(loadbuf);
            wait();

            if (size < 0) {
                puts("\nXMODEM receive error!\n");
            }
            else {
                puts("\nXMODEM receive succeeded.\n");
            }
        }
        else if (!strcmp(command, "dump")) {
            /* dump コマンド実行 */
            puts("size: ");
            putxval(size, 0);
            puts("\n");
            dump(loadbuf, size);
        }
        else if (!strcmp(command, "run")) {
            /* run コマンドの実行 */
            EntryPoint entry_point = elf_load(loadbuf);

            if (!entry_point) {
                puts("run error!\n");
            }
            else {
                puts("starting from entry point: ");
                putxval((unsigned long)entry_point, 0);
                puts("\n");
                entry_point();
                /* WON'T COME BACK HERE */
            }
        }
        else {
            puts("unknown.\n");
        }
    }

    return 0;
}
