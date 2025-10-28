#include "../../../code/core/impl/string/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    Pax_Buffer32 buffer0 = pax_buffer32_create(&arena, 16);
    Pax_Buffer32 buffer1 = pax_buffer32_create(&arena, 16);

    pax_buffer32_write_tail_memory32(&buffer0,
        pax_block_from_vargs(paxu32, 'c', 'i', 'a', 'o'), 4);

    paxiword size = pax_buffer32_peek_buffer32(&buffer0, 2, &buffer1);

    for (paxiword i = 0; i < pax_buffer32_length(&buffer0); i += 1) {
        paxi32 item = pax_buffer32_peek_unicode_or_none(&buffer0, i);

        printf("\\x%08lx", item);

        if (pax_unicode_is_ascii(item) != 0 && pax_unicode_is_ascii_cntrl(item) == 0)
            printf(", %c", pax_as(paxu8, item));

        printf("\n");
    }

    printf("\nvs\n\n");

    for (paxiword i = 0; i < pax_buffer32_length(&buffer1); i += 1) {
        paxi32 item = pax_buffer32_peek_unicode_or_none(&buffer0, i);

        printf("\\x%08lx", item);

        if (pax_unicode_is_ascii(item) != 0 && pax_unicode_is_ascii_cntrl(item) == 0)
            printf(", %c", pax_as(paxu8, item));

        printf("\n");
    }
}
