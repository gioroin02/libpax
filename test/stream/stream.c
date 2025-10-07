#include "../../code/impl/stream/export.h"

#include <stdio.h>

void
read_byte_per_byte(Pax_Source* source)
{
    paxu8 byte = pax_source_read_byte(source);

    printf("read = [\n");

    while (byte != 0) {
        printf("%3u", byte);

        if (byte > 0x20 && byte < 0x80)
            printf(" (%c)", byte);

        printf("\n");

        byte = pax_source_read_byte(source);
    }

    printf("]\n");
}

void
read_string8(Pax_Source* source, Pax_Arena* arena, paxiword length)
{
    Pax_String8 string = pax_source_read_string8(source, arena, length);

    printf("string8 = [\n");

    for (paxiword i = 0; i < string.length; i += 1) {
        printf("%3u", string.memory[i]);

        if (string.memory[i] > 0x20 && string.memory[i] < 0x80)
            printf(" (%c)", string.memory[i]);

        printf("\n");
    }

    printf("]\n");
}

int
main(int argc, char** argv)
{
    paxu8 memory[PAX_MEMORY_KIB] = {0};

    Pax_Arena arena = pax_arena_make(memory, pax_size(memory));

    Pax_Buffer8 buffer = pax_buffer8_create(&arena, 256);
    Pax_Source* source = pax_source_from_buffer8(&arena, &buffer);
    Pax_Target* target = pax_target_from_buffer8(&arena, &buffer);

    pax_target_write_string8(target, pax_str8("ciao\narrivederci"));

    read_byte_per_byte(source);

    pax_target_write_string8(target, pax_str8("ciao\narrivederci"));

    read_string8(source, &arena, 8);
}
