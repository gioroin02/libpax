#include "../../../code/core/impl/storage/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    Pax_Path path = pax_path_create(&arena, PAX_MEMORY_KIB);

    pax_path_insert_string8(&path, pax_current_directory(&arena, PAX_MEMORY_KIB), pax_str8("/"));
    pax_path_insert_string8(&path, pax_str8("test\\..\\subdir\\."), pax_str8("\\"));

    Pax_String16 string = pax_string16_from_path(&arena, &path, PAX_ASCII_BACK_SLASH);

    wprintf(L"'%.*s'\n", pax_as(int, string.length), string.memory);
}
