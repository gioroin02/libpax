#include "../../code/impl/memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    printf("0x%012llx, %lli\n",
        pax_as(paxuword, arena.memory), arena.capacity);

    pax_memory_release(&arena);
}
