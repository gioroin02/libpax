#include "../../code/impl/process/export.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

#define TRUE  GRN("T")
#define FALSE RED("F")

paxuword
generator_proc(Pax_Channel* channel)
{
    if (channel == 0) return 0;

    for (paxiword i = 0; i < 26; i += 1) {
        pax_channel_insert(channel, paxu8,
            pax_block_from_vargs(paxu8, 'A' + i));

        pax_current_thread_sleep(rand() % 250);
    }

    pax_channel_insert(channel, paxu8,
        pax_block_from_vargs(paxu8, 0));

    return 1;
}

int
main(int argc, char** argv)
{
    Pax_Arena   arena   = pax_memory_reserve(16);
    Pax_Channel channel = pax_channel_create(&arena, paxu8, 1024);

    srand(time(0));

    printf("Threads start...\n");

    Pax_Thread generator =
        pax_thread_start(&arena, &channel, &generator_proc);

    paxu8 byte = 0;

    for (paxiword i = 0; i < 10; i += 1) {
        paxb8 state =
            pax_channel_remove(&channel, paxu8, &byte);

        if (state != 0 && byte == 0) break;

        printf("%c\n", byte);
    }

    printf("Threads wait...\n");

    pax_thread_wait(generator);

    while (1) {
        paxb8 state =
            pax_channel_remove(&channel, paxu8, &byte);

        if (state != 0 && byte == 0) break;

        printf("%c\n", byte);
    }

    printf("Threads stop...\n");
}
