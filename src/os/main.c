#include "defines.h"
#include "intr.h"
#include "interrupt.h"
#include "serial.h"
#include "lib.h"

static void intr(softvec_type_t type, unsigned long sp)
{
    int c;
    static char command[32];
    static int len;

    c = getchar();

    if (c != '\n') {
        command[len++] = c;
    }
    else {
        command[len++] = '\0';

        if (!strncmp(command, "echo", 4)) {
            /* echo コマンド実行 */
            puts(command + 4);
            puts("\n");
        }
        else {
            puts("unknown\n");
        }

        puts("> ");
        len = 0;
    }
}

int main(void)
{
    INTR_DISABLE();

    puts("kozos boot succeed!\n");

    softvec_setintr(SOFTVEC_TYPE_SERINTR, intr);
    serial_intr_recv_enable(SERIAL_DEFAULT_DEVICE);

    puts("> ");

    INTR_ENABLE();

    while (1) {
        asm volatile ("sleep");
    }

    return 0;
}
