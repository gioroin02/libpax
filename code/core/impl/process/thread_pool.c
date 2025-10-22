#ifndef PAX_CORE_PROCESS_THREAD_POOL_C
#define PAX_CORE_PROCESS_THREAD_POOL_C

#include "./thread_pool.h"

static void
pax_worker_proc(Pax_Thread_Pool* pool)
{
    while (1) {
        Pax_Worker_Task task = {0};

        pax_channel_remove(&pool->tasks, Pax_Worker_Task, &task);

        Pax_Worker_Result result = task.result;

        if (task.proc != 0) {
            Pax_Worker_Proc* proc = pax_as(Pax_Worker_Proc*, task.proc);

            proc(task.ctxt,
                result.kind, result.memory, result.length);
        } else
            break;

        pax_channel_insert(&pool->results, Pax_Worker_Result, &result);
    }
}

Pax_Thread_Pool*
pax_thread_pool_create(Pax_Arena *arena, paxiword threads, paxiword tasks)
{
    Pax_Thread_Pool temp = {
        .threads = pax_array_create(arena, Pax_Thread, threads),
        .tasks   = pax_channel_create(arena, Pax_Worker_Task, tasks),
        .results = pax_channel_create(arena, Pax_Worker_Result, tasks),
    };

    Pax_Thread_Pool* result = pax_arena_clone(arena, Pax_Thread_Pool, &temp, 1);

    if (result == 0) return 0;

    for (paxiword i = 0; i < pax_array_capacity(&result->threads); i += 1) {
        Pax_Thread thread =
            pax_thread_start(arena, result, &pax_worker_proc);

        pax_array_insert(&result->threads, Pax_Thread,
            pax_array_tail(&result->threads) + 1, &thread, 1);
    }

    return result;
}

void
pax_thread_pool_destroy(Pax_Thread_Pool* self)
{
    if (self == 0) return;

    for (paxiword i = 0; i < pax_array_capacity(&self->threads); i += 1) {
        Pax_Worker_Task task = {0};

        pax_channel_insert(&self->tasks,
            Pax_Worker_Task, &task);
    }

    while (pax_array_length(&self->threads) > 0) {
        Pax_Thread thread = 0;

        pax_array_remove(&self->threads, Pax_Thread,
            pax_array_tail(&self->threads), &thread, 1);

        pax_thread_wait(thread);
    }

    pax_channel_destroy(&self->results);
    pax_channel_destroy(&self->tasks);
}

paxb8
pax_thread_pool_insert(Pax_Thread_Pool* self, Pax_Worker_Result value, void* ctxt, void* proc)
{
    Pax_Worker_Task task = {
        .ctxt   = ctxt,
        .proc   = proc,
        .result = value,
    };

    if (task.proc == 0) return 0;

    return pax_channel_insert(&self->tasks,
        Pax_Worker_Task, &task);
}

paxb8
pax_thread_pool_try_insert(Pax_Thread_Pool* self, Pax_Worker_Result value, void* ctxt, void* proc)
{
    Pax_Worker_Task task = {
        .ctxt   = ctxt,
        .proc   = proc,
        .result = value,
    };

    if (task.proc == 0) return 0;

    return pax_channel_try_insert(&self->tasks,
        Pax_Worker_Task, &task);
}

paxb8
pax_thread_pool_remove(Pax_Thread_Pool* self, Pax_Worker_Result* value)
{
    Pax_Worker_Result temp = {0};

    if (pax_channel_remove(&self->results, Pax_Worker_Result, &temp) == 0)
        return 0;

    if (value != 0) *value = temp;

    return 1;
}

paxb8
pax_thread_pool_try_remove(Pax_Thread_Pool* self, Pax_Worker_Result* value)
{
    Pax_Worker_Result temp = {0};

    if (pax_channel_try_remove(&self->results, Pax_Worker_Result, &temp) == 0)
        return 0;

    if (value != 0) *value = temp;

    return 1;
}

Pax_Worker_Result
pax_worker_result_compress_pure(paxiword kind, void* memory, paxiword length)
{
    return (Pax_Worker_Result) {
        .kind   = kind,
        .memory = memory,
        .length = length,
    };
}

paxb8
pax_worker_result_extract_pure(Pax_Worker_Result self, void *memory, paxiword length)
{
    if (self.length != length || memory == 0)
        return 0;

    Pax_Slice slice =
        pax_slice_make(self.memory, self.length, 1);

    Pax_Slice other = pax_slice_make(memory, length, 1);

    pax_slice_read(slice, 0, other);

    return 1;
}

#endif // PAX_CORE_PROCESS_THREAD_POOL_C
