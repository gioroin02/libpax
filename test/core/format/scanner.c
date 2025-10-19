#include "../../code/impl/format/export.h"

#include <stdio.h>

paxb8
pax_byte_is_cntrl(paxu8 byte)
{
    if (byte >= 0x00 && byte <= 0x20)
        return 1;

    return 0;
}

int
main(int argc, char** argv)
{
    Pax_Arena   arena  = pax_memory_reserve(16);
    Pax_Buffer8 buffer = pax_buffer8_create(&arena, PAX_MEMORY_KIB);

    Pax_Scanner scanner = pax_scanner_create(&arena, 16,
        pax_source_from_buffer8(&arena, &buffer));

    pax_buffer8_write_tail_string8(&buffer, pax_str8("ciao sono mario"));

    paxiword mark = pax_arena_tell(&arena);

    while (1) {
        Pax_String8 item = pax_scanner_read_until(&scanner,
            0, &arena, 16, &pax_byte_is_cntrl);

        if (item.length <= 0) break;

        printf("'%.*s'\n", pax_as(int, item.length),
            item.memory);

        // pax_scanner_drop(&scanner, item.length);

        Pax_String8 drop = pax_scanner_read_while(&scanner,
            0, &arena, 16, &pax_byte_is_cntrl);

        // pax_scanner_drop(&scanner, drop.length);

        pax_arena_rewind(&arena, mark, 0);
    }
}
