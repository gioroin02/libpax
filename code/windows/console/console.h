#ifndef PAX_WINDOWS_CONSOLE_CONSOLE_H
#define PAX_WINDOWS_CONSOLE_CONSOLE_H

#include "./import.h"

typedef struct Pax_Windows_Console Pax_Windows_Console;

Pax_Windows_Console*
pax_windows_console_create(Pax_Arena* arena);

void
pax_windows_console_destroy(Pax_Windows_Console* self);

paxb8
pax_windows_console_mode_apply(Pax_Windows_Console* self, Pax_Console_Mode mode);

Pax_Console_Mode
pax_windows_console_mode_query(Pax_Windows_Console* self);

paxiword
pax_windows_console_write(Pax_Windows_Console* self, paxu8* memory, paxiword length);

paxiword
pax_windows_console_read(Pax_Windows_Console* self, paxu8* memory, paxiword length);

#endif // PAX_WINDOWS_CONSOLE_CONSOLE_H
