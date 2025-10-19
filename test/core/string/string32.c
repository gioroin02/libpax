#include "../../code/impl/string/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    Pax_String32 string0 = pax_string32_copy_memory32(&arena,
        pax_block_from_vargs(paxu32, 'c', 'i', 'a', 'o'), 4);

    Pax_String32 string1 = pax_string32_copy_unicode(&arena, 0x1f600);

    for (paxiword i = 0; i < string0.length; i += 1) {
        paxu32 item = pax_string32_peek_or_none(string0, i);

        printf("\\x%08lx", item);

        if (pax_unicode_is_ascii(item) != 0 && pax_unicode_is_ascii_cntrl(item) == 0)
            printf(", %c", pax_as(paxu8, item));

        printf("\n");
    }

    for (paxiword i = 0; i < string1.length; i += 1) {
        paxu32 item = pax_string32_peek_or_none(string1, i);

        printf("\\x%08lx", item);

        if (pax_unicode_is_ascii(item) != 0 && pax_unicode_is_ascii_cntrl(item) == 0)
            printf(", %c", pax_as(paxu8, item));

        printf("\n");
    }
}
