#ifndef PAX_CORE_MEMORY_ARRAY_RING_H
#define PAX_CORE_MEMORY_ARRAY_RING_H

#include "arena.h"

#define pax_array_ring_create(arena, type, amount) \
    pax_array_ring_create_pure(arena, amount, pax_size(type))

#define pax_array_ring_insert_head(self, type, value) \
    pax_array_ring_insert_pure_head(self, value, pax_size(type))

#define pax_array_ring_insert_tail(self, type, value) \
    pax_array_ring_insert_pure_tail(self, value, pax_size(type))

#define pax_array_ring_remove_head(self, type, value) \
    pax_array_ring_remove_pure_head(self, value, pax_size(type))

#define pax_array_ring_remove_tail(self, type, value) \
    pax_array_ring_remove_pure_tail(self, value, pax_size(type))

#define pax_array_ring_peek(self, type, index, value) \
    pax_array_ring_peek_pure(self, index, value, pax_size(type))

#define pax_array_ring_peek_or_fail(self, type, index) \
    *pax_as(type*, pax_array_ring_peek_pure_or_null(self, index))

#define pax_array_ring_update(self, type, index, value) \
    pax_array_ring_update_pure(self, index, value, pax_size(type))

typedef struct Pax_Array_Ring
{
    paxu8*   memory;
    paxiword length;
    paxiword stride;
    paxiword capacity;
    paxiword head;
    paxiword tail;
}
Pax_Array_Ring;

Pax_Array_Ring
pax_array_ring_create_pure(Pax_Arena* arena, paxiword length, paxiword stride);

Pax_Array_Ring
pax_array_ring_copy(Pax_Arena* arena, Pax_Array_Ring* value);

void
pax_array_ring_normalize(Pax_Array_Ring* self);

void
pax_array_ring_clear(Pax_Array_Ring* self);

void
pax_array_ring_fill(Pax_Array_Ring* self);

paxiword
pax_array_ring_length(Pax_Array_Ring* self);

paxiword
pax_array_ring_capacity(Pax_Array_Ring* self);

paxiword
pax_array_ring_head(Pax_Array_Ring* self);

paxiword
pax_array_ring_tail(Pax_Array_Ring* self);

paxb8
pax_array_ring_is_empty(Pax_Array_Ring* self);

paxb8
pax_array_ring_is_full(Pax_Array_Ring* self);

paxb8
pax_array_ring_insert_pure_head(Pax_Array_Ring* self, void* memory, paxiword stride);

paxb8
pax_array_ring_insert_pure_tail(Pax_Array_Ring* self, void* memory, paxiword stride);

paxb8
pax_array_ring_remove_pure_head(Pax_Array_Ring* self, void* memory, paxiword stride);

paxb8
pax_array_ring_remove_pure_tail(Pax_Array_Ring* self, void* memory, paxiword stride);

paxb8
pax_array_ring_peek_pure(Pax_Array_Ring* self, paxiword index, void* memory, paxiword stride);

void*
pax_array_ring_peek_pure_or_null(Pax_Array_Ring* self, paxiword index);

paxb8
pax_array_ring_update_pure(Pax_Array_Ring* self, paxiword index, void* memory, paxiword stride);

#endif // PAX_CORE_MEMORY_RING_ARRAY_H
