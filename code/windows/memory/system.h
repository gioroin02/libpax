#ifndef PAX_WINDOWS_MEMORY_SYSTEM_H
#define PAX_WINDOWS_MEMORY_SYSTEM_H

#include "./import.h"

paxiword
pax_windows_memory_page_size();

Pax_Arena
pax_windows_memory_reserve(paxiword amount);

void
pax_windows_memory_release(Pax_Arena* arena);

#endif // PAX_WINDOWS_MEMORY_SYSTEM_H
