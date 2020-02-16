#include "defines.h"
#include "serial.h"
#include "lib.h"

int a1 = 1;
static int a2 = 2;
int a3;
static int a4;

int main(void)
{
    int a5;
    int a6 = 6;
    static int a7 = 7;
    static int a8;

    serial_init(SERIAL_DEFAULT_DEVICE);

    puts("Hello World!\n");

    putxval(0x10, 0);
    puts("\n");
    putxval(0xffff, 0);
    puts("\n");

    while (1) {
        /* DO NOTHING */
    }

    return 0;
}
