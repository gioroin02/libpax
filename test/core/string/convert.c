#include "../../../code/core/impl/string/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    Pax_String8  string0 = pax_string8_copy_unicode(&arena, 0x1f600);
    Pax_String16 string1 = pax_string16_copy_string8(&arena, string0);
    Pax_String32 string2 = pax_string32_copy_string16(&arena, string1);

    printf("string8 = {\n");
    for (paxiword i = 0; i < string0.length; i += 1) {
        paxu8 item = pax_string8_peek_or_none(string0, i);

        printf("\\x%02x", item);

        if (pax_unicode_is_ascii(item) != 0 && pax_unicode_is_ascii_cntrl(item) == 0)
            printf(", %c", item);

        printf("\n");
    }
    printf("}\n");

    printf("string16 = {\n");
    for (paxiword i = 0; i < string1.length; i += 1) {
        paxu16 item = pax_string16_peek_or_none(string1, i);

        printf("\\x%04x", item);

        if (pax_unicode_is_ascii(item) != 0 && pax_unicode_is_ascii_cntrl(item) == 0)
            printf(", %c", pax_as(paxu8, item));

        printf("\n");
    }
    printf("}\n");

    printf("string32 = {\n");
    for (paxiword i = 0; i < string2.length; i += 1) {
        paxu32 item = pax_string32_peek_or_none(string2, i);

        printf("\\x%08lx", item);

        if (pax_unicode_is_ascii(item) != 0 && pax_unicode_is_ascii_cntrl(item) == 0)
            printf(", %c", pax_as(paxu8, item));

        printf("\n");
    }
    printf("}\n");
}
