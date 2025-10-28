#include "../../../code/core/impl/memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    paxu8 memory[256] = {0};

    Pax_Arena arena = pax_arena_from_block(memory);
    Pax_Array array = pax_array_create(&arena, paxu32, 6);

    pax_array_insert(&array, paxu32, pax_array_tail(&array) + 1,
        pax_block_from_vargs(paxu32, 11, 22, 33), 3);

    printf("array = ");
    for (paxiword i = 0; i < array.length; i += 1)
        printf("[ %2lu ]", pax_array_peek_or_fail(&array, paxu32, i));
    printf("\n");

    paxu32 items[2] = {0};

    pax_array_remove(&array, paxu32, 0, items, 2);

    printf("items = [ %2lu ][ %2lu ]\n", items[0], items[1]);

    printf("array = ");
    for (paxiword i = 0; i < array.length; i += 1)
        printf("[ %2lu ]", pax_array_peek_or_fail(&array, paxu32, i));
    printf("\n");

    pax_array_remove(&array, paxu32, 0, 0, 1);

    printf("array = ");
    for (paxiword i = 0; i < array.length; i += 1)
        printf("[ %2lu ]", pax_array_peek_or_fail(&array, paxu32, i));
    printf("\n");

    pax_array_insert(&array, paxu32, 0, pax_block_from_vargs(paxu32, 5, 10, 15, 20, 25, 30, 35, 40), 8);

    pax_array_update(&array, paxu32, 0, pax_block_from_vargs(paxu32, 1), 1);
    pax_array_update(&array, paxu32, 1, pax_block_from_vargs(paxu32, 2, 3, 4), 3);

    printf("array = ");
    for (paxiword i = 0; i < array.length; i += 1)
        printf("[ %2lu ]", pax_array_peek_or_fail(&array, paxu32, i));
    printf("\n");
}
