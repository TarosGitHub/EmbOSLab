#include "defines.h"
#include "serial.h"
#include "lib.h"

int main(void)
{
    static char command[32];

    puts("Hello World\n");

    while (1) {
        /* コマンド受付 */
        puts("> ");
        gets(command);

        if (!strncmp(command, "echo", 4)) {
            /* echo コマンド実行 */
            puts(command + 4);
            puts("\n");
        }
        else if (!strcmp(command, "exit")) {
            /* exit コマンド実行 */
            break;
        }
        else {
            puts("unknown.\n");
        }
    }

    return 0;
}
