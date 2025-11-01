#include "../../../code/core/impl/format/export.h"

#include <stdio.h>

paxiword
pax_scanner_read_ascii(Pax_Scanner* self, paxu8* memory, paxiword length)
{
    paxu8    byte = 0;
    paxiword size = 0;

    while (pax_scanner_peek_byte(self, 0, &byte) > 0) {
        if (pax_unicode_is_ascii_cntrl(byte) != 0)
            break;

        memory[size] = byte;

        size += pax_scanner_drop(self, 1);
    }

    return size;
}

int
main(int argc, char** argv)
{
    Pax_Arena   arena  = pax_memory_reserve(16);
    Pax_Buffer8 buffer = pax_buffer8_create(&arena, PAX_MEMORY_KIB);

    Pax_Scanner scanner = pax_scanner_create(&arena, 16,
        pax_source_from_buffer8(&arena, &buffer));

    pax_buffer8_write_tail_string8(&buffer, pax_str8("true truee true"));

    paxiword mark = pax_arena_tell(&arena);

    while (1) {
        paxu8 byte = pax_scanner_drop_cntrls(&scanner);

        Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
        Pax_Format_Flag  flags = PAX_FORMAT_FLAG_PLUS;

        paxiword length = 16;
        paxu8*   memory = pax_arena_reserve(&arena, paxu8, length + 1);

        paxiword size = pax_scanner_read_ascii(&scanner, memory, length);

        if (size <= 0) break;

        printf("[%.*s]\n", pax_as(int, size), memory);

        pax_arena_rewind(&arena, mark, 0);
    }
}
