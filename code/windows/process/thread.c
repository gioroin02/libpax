#ifndef PAX_WINDOWS_PROCESS_THREAD_C
#define PAX_WINDOWS_PROCESS_THREAD_C

#include "./thread.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct Pax_Windows_Thread
{
    HANDLE handle;
};

typedef LPTHREAD_START_ROUTINE Pax_Windows_Thread_Proc;

Pax_Windows_Thread*
pax_windows_thread_start(Pax_Arena* arena, void* ctxt, void* proc)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Windows_Thread* result =
        pax_arena_reserve(arena, Pax_Windows_Thread, 1);

    if (result != 0) {
        Pax_Windows_Thread_Proc routine =
            pax_as(Pax_Windows_Thread_Proc, proc);

        result->handle = CreateThread(0, 0, routine, ctxt, 0, 0);

        if (result->handle != 0)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_windows_thread_wait(Pax_Windows_Thread* self)
{
    if (self == 0) return;

    WaitForSingleObject(self->handle, INFINITE);

    if (self->handle != 0)
        CloseHandle(self->handle);

    self->handle = 0;
}

void
pax_windows_thread_detach(Pax_Windows_Thread* self)
{
    if (self->handle != 0)
        CloseHandle(self->handle);

    self->handle = 0;
}

#endif // PAX_WINDOWS_PROCESS_THREAD_C
