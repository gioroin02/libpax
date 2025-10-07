#ifndef PAX_WINDOWS_PROCESS_SYSTEM_C
#define PAX_WINDOWS_PROCESS_SYSTEM_C

#include "./system.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

paxiword
pax_windows_process_core_amount()
{
    SYSTEM_INFO info = {};

    GetSystemInfo(&info);

    return pax_as(paxiword, info.dwNumberOfProcessors);
}

void
pax_windows_current_thread_sleep(paxuword millis)
{
    Sleep(millis);
}

paxiword
pax_windows_current_thread_ident()
{
    return pax_as(paxiword, GetCurrentThreadId());
}

#endif // PAX_WINDOWS_PROCESS_SYSTEM_C
