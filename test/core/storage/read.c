#include "../../../code/core/impl/storage/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    Pax_File file = pax_default_input(&arena);

    if (argc >= 2) {
        paxiword length = 128;
        paxiword stride = pax_size(paxu8);

        Pax_String8 base = pax_str8(".");
        Pax_String8 name = pax_string8_from_memory(argv[1], length, stride);

        file = pax_file_open(&arena, base, name, PAX_FILE_MODE_RD);
    }

    if (file != 0) printf("%016llx\n", *pax_as(paxuword*, &file));

    Pax_Buffer8 buffer = pax_buffer8_create(&arena, 256);
    Pax_Source* source = pax_source_from_file(&arena, file);

    while (1) {
        if (pax_source_read_buffer8(source, &buffer) == 0)
            break;

        printf("%.*s", pax_as(int, buffer.length),
            buffer.memory);

        pax_buffer8_clear(&buffer);
    }

    pax_file_close(file);
}
