#include "defines.h"
#include "intr.h"
#include "interrupt.h"

int softvec_init(void)
{
    SOFTVECS[SOFTVEC_TYPE_SOFTERR] = NULL;
    SOFTVECS[SOFTVEC_TYPE_SYSCALL] = NULL;
    SOFTVECS[SOFTVEC_TYPE_SERINTR] = NULL;

    return 0;
}

int softvec_setintr(softvec_type_t type, softvec_handler_t handler)
{
    SOFTVECS[type] = handler;

    return 0;
}

void interrupt(softvec_type_t type, unsigned long sp)
{
    softvec_handler_t handler = SOFTVECS[type];

    if (handler) {
        /* ハンドラが設定されていれば呼び出す */
        handler(type, sp);
    }
}
