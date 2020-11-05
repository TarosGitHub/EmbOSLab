#include "defines.h"
#include "kozos.h"
#include "lib.h"

int test08_1_main(int argc, char* argv[])
{
    static char command[32];

    puts("test08_1 started.\n");

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

    puts("test08_1 exit.\n");

    return 0;
}
