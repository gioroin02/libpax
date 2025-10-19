#ifndef PAX_WINDOWS_STORAGE_DIRECTORY_H
#define PAX_WINDOWS_STORAGE_DIRECTORY_H

#include "./import.h"

paxiword
pax_windows_current_directory_memory8(Pax_Arena* arena, paxu8* memory, paxiword length);

Pax_String8
pax_windows_current_directory(Pax_Arena* arena, paxiword length);

#endif // PAX_WINDOWS_STORAGE_DIRECTORY_H
