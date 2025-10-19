#ifndef PAX_LINUX_PROCESS_SYSTEM_C
#define PAX_LINUX_PROCESS_SYSTEM_C

#include "./system.h"

#if !defined(_POSIX_C_SOURCE)

    #define _POSIX_C_SOURCE 200809L

#endif

#include <unistd.h>
#include <time.h>

#include <pthread.h>

typedef struct timespec Pax_Time_Spec;

paxiword
pax_linux_process_core_amount()
{
    long result = sysconf(_SC_NPROCESSORS_ONLN);

    if (result > 0)
        return pax_as(paxiword, result);

    return 0;
}

void
pax_linux_current_thread_sleep(paxuword millis)
{
    Pax_Time_Spec spec;

    spec.tv_sec  = (millis / 1000);
    spec.tv_nsec = (millis % 1000) * 1000000;

    nanosleep(&spec, 0);
}

paxiword
pax_linux_current_thread_ident()
{
    return pax_as(paxiword, pthread_self());
}

#endif // PAX_LINUX_PROCESS_SYSTEM_C
