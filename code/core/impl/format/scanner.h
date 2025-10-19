#ifndef PAX_CORE_FORMAT_SCANNER_H
#define PAX_CORE_FORMAT_SCANNER_H

#include "./import.h"

typedef struct Pax_Scanner
{
    Pax_Buffer8 buffer;
    Pax_Source* source;
}
Pax_Scanner;

typedef paxb8 (Pax_Scanner_Proc) (paxu8);

Pax_Scanner
pax_scanner_create(Pax_Arena* arena, paxiword length, Pax_Source* source);

paxiword
pax_scanner_drop(Pax_Scanner* self, paxiword length);

paxiword
pax_scanner_drop_while(Pax_Scanner* self, void* proc);

paxiword
pax_scanner_drop_until(Pax_Scanner* self, void* proc);

paxiword
pax_scanner_read_memory8(Pax_Scanner* self, paxiword offset, paxu8* memory, paxiword length);

Pax_String8
pax_scanner_read_while(Pax_Scanner* self, paxiword offset, Pax_Arena* arena, paxiword length, void* proc);

Pax_String8
pax_scanner_read_until(Pax_Scanner* self, paxiword offset, Pax_Arena* arena, paxiword length, void* proc);

paxiword
pax_scanner_peek_memory8(Pax_Scanner* self, paxiword offset, paxu8* memory, paxiword length);

Pax_String8
pax_scanner_peek_while(Pax_Scanner* self, paxiword offset, Pax_Arena* arena, paxiword length, void* proc);

Pax_String8
pax_scanner_peek_until(Pax_Scanner* self, paxiword offset, Pax_Arena* arena, paxiword length, void* proc);

#endif // PAX_CORE_FORMAT_SCANNER_H
