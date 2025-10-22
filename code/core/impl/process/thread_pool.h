#ifndef PAX_CORE_PROCESS_THREAD_POOL_H
#define PAX_CORE_PROCESS_THREAD_POOL_H

#include "./channel.h"
#include "./thread.h"

#define pax_worker_result_compress(type, kind, value) \
    pax_worker_result_compress_pure(kind, value, pax_size(type))

#define pax_worker_result_extract(self, type, value) \
    pax_worker_result_extract_pure(self, value, pax_size(type))

typedef struct Pax_Thread_Pool
{
    Pax_Array   threads;
    Pax_Channel tasks;
    Pax_Channel results;
}
Pax_Thread_Pool;

typedef struct Pax_Worker_Result
{
    paxiword kind;
    void*    memory;
    paxiword length;
}
Pax_Worker_Result;

typedef struct Pax_Worker_Task
{
    void* ctxt;
    void* proc;

    Pax_Worker_Result result;
}
Pax_Worker_Task;

typedef void (Pax_Worker_Proc) (void*, paxiword, void*, paxiword);

/* Thread Pool */

Pax_Thread_Pool*
pax_thread_pool_create(Pax_Arena* arena, paxiword threads, paxiword tasks);

void
pax_thread_pool_destroy(Pax_Thread_Pool* self);

paxb8
pax_thread_pool_insert(Pax_Thread_Pool* self, Pax_Worker_Result value, void* ctxt, void* proc);

paxb8
pax_thread_pool_try_insert(Pax_Thread_Pool* self, Pax_Worker_Result value, void* ctxt, void* proc);

paxb8
pax_thread_pool_remove(Pax_Thread_Pool* self, Pax_Worker_Result* value);

paxb8
pax_thread_pool_try_remove(Pax_Thread_Pool* self, Pax_Worker_Result* value);

/* Result */

Pax_Worker_Result
pax_worker_result_compress_pure(paxiword kind, void* memory, paxiword length);

paxb8
pax_worker_result_extract_pure(Pax_Worker_Result self, void* memory, paxiword length);

#endif // PAX_CORE_PROCESS_THREAD_POOL_H
