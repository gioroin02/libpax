#include "../../../code/core/impl/process/export.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

typedef enum Task_Kind
{
    TASK_NONE,
    TASK_CREATE,
    TASK_READ,
    TASK_WRITE,
}
Task_Kind;

typedef struct Task
{
    Task_Kind kind;

    Pax_Arena arena;

    union
    {
        struct
        {
            paxu8*   memory;
            paxiword length;
        };
    };
}
Task;

typedef struct Result
{
    Task_Kind kind;

    union
    {
        struct
        {
            paxu8*   memory;
            paxiword length;
            paxiword size;
        };

        paxiword* temp;
    };
}
Result;

void
task_proc(Task* self, paxiword kind, Result* result, paxiword stride)
{
    if (self == 0 || result == 0) return;

    result->kind = self->kind;

    switch (self->kind) {
        case TASK_CREATE: {
            result->temp = pax_arena_reserve(
                &self->arena, paxiword, 1);

            if (result->temp != 0)
                *result->temp = -1;
        } break;

        case TASK_READ: {
            paxiword temp = rand() % (self->length + 1);

            result->memory = self->memory;
            result->length = self->length;

            result->size = temp;

            for (paxiword i = 0; i < result->size; i += 1)
                self->memory[i] = 0xff;
        } break;

        case TASK_WRITE: {
            result->memory = self->memory;
            result->length = self->length;
            result->size   = 0;
        } break;

        default: break;
    }

    if (self->kind != TASK_NONE)
        pax_current_thread_sleep(rand() % 128);
    else
        pax_current_thread_sleep(500);
}

Task
task_none()
{
    return (Task) {.kind = TASK_NONE};
}

Task
task_create(Pax_Arena* arena, paxiword length)
{
    return (Task) {
        .kind  = TASK_CREATE,
        .arena = pax_arena_create(arena, length),
    };
}

Task
task_read(Pax_Arena* arena, paxiword length)
{
    paxu8* memory =
        pax_arena_reserve(arena, paxu8, length);

    if (memory == 0) return (Task) {0};

    return (Task) {
        .kind   = TASK_READ,
        .memory = memory,
        .length = length,
    };
}

Task
task_write(Pax_Arena* arena, paxiword length)
{
    paxu8* memory =
        pax_arena_reserve(arena, paxu8, length);

    if (memory == 0) return (Task) {0};

    return (Task) {
        .kind   = TASK_WRITE,
        .memory = memory,
        .length = length,
    };
}

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    Pax_Thread_Pool* pool =
        pax_thread_pool_create(&arena, 8, 32);

    srand(time(0));

    paxiword amount = 64;

    for (paxiword i = 0; i <= amount; i += 1) {
        Task*   task   = pax_arena_reserve(&arena, Task, 1);
        Result* result = pax_arena_reserve(&arena, Result, 1);

        *task = task_none();

        if (i + 1 <= amount) {
            switch (i % 3) {
                case 0: *task = task_create(&arena, 16); break;
                case 1: *task = task_read(&arena, 16);   break;
                case 2: *task = task_write(&arena, 16);  break;

                default: break;
            }
        }

        if (result != 0 && task != 0) {
            Pax_Worker_Result value =
                pax_worker_result_compress(Result, 0, result);

            pax_thread_pool_insert(pool, value, task, &task_proc);
        }
    }

    for (paxiword i = 0; 1; i += 1) {
        Pax_Worker_Result value = {0};

        if (pax_thread_pool_remove(pool, &value) == 0)
            break;

        if (value.kind != 0) break;

        Result result = {0};

        pax_worker_result_extract(value, Result, &result);

        if (result.kind == TASK_NONE) break;

        printf("[%4lli] ", i);

        switch (result.kind) {
            case TASK_CREATE: {
                printf("CREATE = {");

                if (result.temp != 0)
                    printf("%lli", *result.temp);
                else
                    printf("null");

                printf("}\n");
            } break;

            case TASK_READ: {
                printf("READ   = {[");

                for (paxiword i = 0; i < result.size; i += 1) {
                    printf("%u", result.memory[i]);

                    if (i + 1 < result.size)
                        printf(" ");
                }

                printf("] %lli}\n", result.size);
            } break;

            case TASK_WRITE: {
                printf("WRITE  = {}\n");
            } break;

            default: break;
        }
    }

    pax_thread_pool_destroy(pool);
}
