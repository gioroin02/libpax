#include "../../../code/core/impl/storage/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    Pax_String8 base = pax_str8(".");
    Pax_String8 name = pax_str8("456undfglkjn34.txt");

    Pax_File file = pax_file_create(&arena, base, name, PAX_FILE_MODE_RD);

    if (file != 0) printf("%p\n", file);

    getchar();

    pax_file_close(file);
    pax_file_destroy(&arena, base, name);
}
