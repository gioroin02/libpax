#ifndef PAX_WINDOWS_PROCESS_SYSTEM_H
#define PAX_WINDOWS_PROCESS_SYSTEM_H

#include "import.h"

paxiword
pax_windows_process_core_amount();

void
pax_windows_current_thread_sleep(paxuword millis);

paxiword
pax_windows_current_thread_ident();

#endif // PAX_WINDOWS_PROCESS_SYSTEM_H
