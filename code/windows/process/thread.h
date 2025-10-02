#ifndef PAX_WINDOWS_PROCESS_THREAD_H
#define PAX_WINDOWS_PROCESS_THREAD_H

#include "import.h"

typedef struct Pax_Windows_Thread Pax_Windows_Thread;

Pax_Windows_Thread*
pax_windows_thread_start(Pax_Arena* arena, void* ctxt, void* proc);

void
pax_windows_thread_wait(Pax_Windows_Thread* self);

void
pax_windows_thread_detach(Pax_Windows_Thread* self);

#endif // PAX_WINDOWS_PROCESS_THREAD_H
