#ifndef PAX_WINDOWS_TIME_CLOCK_H
#define PAX_WINDOWS_TIME_CLOCK_H

#include "import.h"

typedef struct Pax_Windows_Clock Pax_Windows_Clock;

Pax_Windows_Clock*
pax_windows_clock_create(Pax_Arena* arena);

paxf32
pax_windows_clock_elapsed(Pax_Windows_Clock* self);

#endif // PAX_WINDOWS_TIME_CLOCK_H
