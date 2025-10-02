#ifndef PAX_CORE_PROCESS_SYNCHRO_C
#define PAX_CORE_PROCESS_SYNCHRO_C

#include "synchro.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../windows/process/synchro.c"

    #define __pax_lock_create__  pax_windows_lock_create
    #define __pax_lock_destroy__ pax_windows_lock_destroy
    #define __pax_lock_enter__   pax_windows_lock_enter
    #define __pax_lock_leave__   pax_windows_lock_leave

    #define __pax_cond_create__    pax_windows_cond_create
    #define __pax_cond_destroy__   pax_windows_cond_destroy
    #define __pax_cond_wait__      pax_windows_cond_wait
    #define __pax_cond_signal__    pax_windows_cond_signal
    #define __pax_cond_broadcast__ pax_windows_cond_broadcast

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/process/synchro.c"

    #define __pax_lock_create__  pax_linux_lock_create
    #define __pax_lock_destroy__ pax_linux_lock_destroy
    #define __pax_lock_enter__   pax_linux_lock_enter
    #define __pax_lock_leave__   pax_linux_lock_leave

    #define __pax_cond_create__    pax_linux_cond_create
    #define __pax_cond_destroy__   pax_linux_cond_destroy
    #define __pax_cond_wait__      pax_linux_cond_wait
    #define __pax_cond_signal__    pax_linux_cond_signal
    #define __pax_cond_broadcast__ pax_linux_cond_broadcast

#else

    #error "Unknown platform"

#endif

Pax_Lock
pax_lock_create(Pax_Arena* arena)
{
    return __pax_lock_create__(arena);
}

void
pax_lock_destroy(Pax_Lock self)
{
    __pax_lock_destroy__(self);
}

void
pax_lock_enter(Pax_Lock self)
{
    __pax_lock_enter__(self);
}

void
pax_lock_leave(Pax_Lock self)
{
    __pax_lock_leave__(self);
}

Pax_Cond
pax_cond_create(Pax_Arena* arena)
{
    return __pax_cond_create__(arena);
}

void
pax_cond_destroy(Pax_Cond self)
{
    __pax_cond_destroy__(self);
}

void
pax_cond_wait(Pax_Cond self, Pax_Lock lock)
{
    __pax_cond_wait__(self, lock);
}

void
pax_cond_signal(Pax_Cond self)
{
    __pax_cond_signal__(self);
}

void
pax_cond_broadcast(Pax_Cond self)
{
    __pax_cond_broadcast__(self);
}

#endif // PAX_CORE_PROCESS_SYNCHRO_C
