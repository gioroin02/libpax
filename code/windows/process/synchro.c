#ifndef PAX_WINDOWS_PROCESS_SYNCHRO_C
#define PAX_WINDOWS_PROCESS_SYNCHRO_C

#include "./synchro.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct Pax_Windows_Lock
{
    CRITICAL_SECTION handle;
};

struct Pax_Windows_Cond
{
    CONDITION_VARIABLE handle;
};

Pax_Windows_Lock*
pax_windows_lock_create(Pax_Arena* arena)
{
    Pax_Windows_Lock* result =
        pax_arena_reserve(arena, Pax_Windows_Lock, 1);

    if (result != 0)
        InitializeCriticalSection(&result->handle);

    return result;
}

void
pax_windows_lock_destroy(Pax_Windows_Lock* self)
{
    if (self != 0)
        DeleteCriticalSection(&self->handle);
}

void
pax_windows_lock_enter(Pax_Windows_Lock* self)
{
    EnterCriticalSection(&self->handle);
}

void
pax_windows_lock_leave(Pax_Windows_Lock* self)
{
    LeaveCriticalSection(&self->handle);
}

Pax_Windows_Cond*
pax_windows_cond_create(Pax_Arena* arena)
{
    Pax_Windows_Cond* result =
        pax_arena_reserve(arena, Pax_Windows_Cond, 1);

    if (result != 0)
        InitializeConditionVariable(&result->handle);

    return result;
}

void
pax_windows_cond_destroy(Pax_Windows_Cond* self)
{

}

void
pax_windows_cond_sleep(Pax_Windows_Cond* self, Pax_Windows_Lock* lock)
{
    SleepConditionVariableCS(&self->handle, &lock->handle, INFINITE);
}

void
pax_windows_cond_wake(Pax_Windows_Cond* self)
{
    WakeConditionVariable(&self->handle);
}

void
pax_windows_cond_wake_all(Pax_Windows_Cond* self)
{
    WakeAllConditionVariable(&self->handle);
}
#endif // PAX_WINDOWS_PROCESS_SYNCHRO_C
