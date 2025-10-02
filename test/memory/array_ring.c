#include "../../code/impl/memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    paxu8 memory[256] = {0};

    Pax_Arena      arena = pax_arena_from_block(memory);
    Pax_Array_Ring array = pax_array_ring_create(&arena, paxu32, 6);

    pax_array_ring_insert_tail(&array, paxu32, pax_block_from_vargs(paxu32, 11));
    pax_array_ring_insert_head(&array, paxu32, pax_block_from_vargs(paxu32, 22));
    pax_array_ring_insert_tail(&array, paxu32, pax_block_from_vargs(paxu32, 33));

    for (paxiword i = 0; i < array.length; i += 1)
        printf("[ %2lu ]", pax_array_ring_peek_or_fail(&array, paxu32, i));
    printf("\n");

    pax_array_ring_fill(&array);

    for (paxiword i = 0; i < array.length; i += 1)
        printf("[ %2lu ]", pax_array_ring_peek_or_fail(&array, paxu32, i));
    printf("\n");
}
