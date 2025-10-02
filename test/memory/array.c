#include "../../code/impl/memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    paxu8 memory[256] = {0};

    Pax_Arena arena = pax_arena_from_block(memory);
    Pax_Array array = pax_array_create(&arena, paxu32, 6);

    pax_array_insert(&array, paxu32, pax_array_tail(&array) + 1,
        pax_block_from_vargs(paxu32, 11));

    pax_array_insert(&array, paxu32, pax_array_head(&array),
        pax_block_from_vargs(paxu32, 22));

    pax_array_insert(&array, paxu32, pax_array_tail(&array) + 1,
        pax_block_from_vargs(paxu32, 33));

    for (paxiword i = 0; i < array.length; i += 1)
        printf("[ %2lu ]", pax_array_peek_or_fail(&array, paxu32, i));
    printf("\n");

    paxu32 item = 0;

    pax_array_remove(&array, paxu32, pax_array_tail(&array), &item);

    pax_array_fill(&array);

    printf("[ %2lu ]\n", item);

    for (paxiword i = 0; i < array.length; i += 1)
        printf("[ %2lu ]", pax_array_peek_or_fail(&array, paxu32, i));
    printf("\n");
}
