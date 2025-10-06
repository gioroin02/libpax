#ifndef PAX_WINDOWS_PROCESS_SYNCHRO_H
#define PAX_WINDOWS_PROCESS_SYNCHRO_H

#include "import.h"

typedef struct Pax_Windows_Lock Pax_Windows_Lock;
typedef struct Pax_Windows_Cond Pax_Windows_Cond;

/* Windows Lock */

Pax_Windows_Lock*
pax_windows_lock_create(Pax_Arena* arena);

void
pax_windows_lock_destroy(Pax_Windows_Lock* self);

void
pax_windows_lock_enter(Pax_Windows_Lock* self);

void
pax_windows_lock_leave(Pax_Windows_Lock* self);

/* Windows Cond */

Pax_Windows_Cond*
pax_windows_cond_create(Pax_Arena* arena);

void
pax_windows_cond_destroy(Pax_Windows_Cond* self);

void
pax_windows_cond_sleep(Pax_Windows_Cond* self, Pax_Windows_Lock* lock);

void
pax_windows_cond_wake(Pax_Windows_Cond* self);

void
pax_windows_cond_wake_all(Pax_Windows_Cond* self);

#endif // PAX_WINDOWS_PROCESS_SYNCHRO_H
