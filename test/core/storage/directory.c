#include "../../../code/core/impl/storage/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    Pax_Arena   arena = pax_memory_reserve(16);
    Pax_String8 path  = pax_current_directory(&arena, PAX_MEMORY_KIB);

    printf("%.*s\n", pax_as(int, path.length), path.memory);
}
