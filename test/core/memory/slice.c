#include "../../../code/core/impl/memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    paxu32 memory[8] = {[3] = 44};

    Pax_Slice slice = pax_slice_make(memory, 8, pax_size(paxu32));

    pax_slice_update(slice, paxu32, 0, pax_block_from_vargs(paxu32, 11));
    pax_slice_update(slice, paxu32, 1, pax_block_from_vargs(paxu32, 22));
    pax_slice_update(slice, paxu32, 2, pax_block_from_vargs(paxu32, 33));

    for (paxiword i = 0; i < slice.length; i += 1)
        printf("[ %2lu ]", pax_slice_peek_or_fail(slice, paxu32, i));
    printf("\n");

    pax_slice_shift_forw(slice, 0, 2, 6);

    for (paxiword i = 0; i < slice.length; i += 1)
        printf("[ %2lu ]", pax_slice_peek_or_fail(slice, paxu32, i));
    printf("\n");

    pax_slice_shift_back(slice, 6, 2, 6);

    for (paxiword i = 0; i < slice.length; i += 1)
        printf("[ %2lu ]", pax_slice_peek_or_fail(slice, paxu32, i));
    printf("\n");
}
