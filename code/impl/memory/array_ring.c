#ifndef PAX_CORE_MEMORY_ARRAY_RING_C
#define PAX_CORE_MEMORY_ARRAY_RING_C

#include "array_ring.h"

Pax_Array_Ring
pax_array_ring_create_pure(Pax_Arena* arena, paxiword length, paxiword stride)
{
    Pax_Array_Ring result = {0};

    Pax_Slice slice =
        pax_arena_reserve_slice(arena, length, stride);

    result.memory   = slice.memory;
    result.stride   = slice.stride;
    result.capacity = slice.length;

    return result;
}

Pax_Array_Ring
pax_array_ring_copy(Pax_Arena* arena, Pax_Array_Ring* value)
{
    Pax_Array_Ring result =
        pax_array_ring_create_pure(arena, value->length, value->stride);

    if (result.capacity == 0) return result;

    for (paxiword i = 0; i < value->length; i += 1) {
        paxiword j = (value->head + i) % value->capacity;

        Pax_Slice left  = pax_slice_make(result.memory, i, i + 1, result.stride);
        Pax_Slice right = pax_slice_make(value->memory, j, j + 1, result.stride);

        pax_slice_copy(left, right);
    }

    return result;
}

void
pax_array_ring_clear(Pax_Array_Ring* self)
{
    self->length = 0;
    self->head   = 0;
    self->tail   = 0;
}

void
pax_array_ring_normalize(Pax_Array_Ring* self)
{
    Pax_Slice slice =
        pax_slice_make(self->memory, 0, self->capacity, self->stride);

    if (self->head > self->tail) {
        paxiword start = 0;
        paxiword stop  = self->capacity - self->head;

        Pax_Slice left =
            pax_slice_make(self->memory, self->head, stop, self->stride);

        Pax_Slice right =
            pax_slice_make(self->memory, start, self->tail, self->stride);

        pax_slice_flip(left);
        pax_slice_flip(right);

        pax_slice_flip(slice);
    }
}

void
pax_array_ring_fill(Pax_Array_Ring* self)
{
    paxiword diff = self->capacity - self->length;

    for (paxiword i = 0; i < diff; i += 1) {
        paxiword index = self->tail;

        Pax_Slice left = pax_slice_make(self->memory,
            index, index + 1, self->stride);

        pax_slice_zero(left);

        self->length += 1;
        self->tail    = (self->tail + 1) % self->capacity;
    }
}

paxiword
pax_array_ring_length(Pax_Array_Ring* self)
{
    return self->length;
}

paxiword
pax_array_ring_capacity(Pax_Array_Ring* self)
{
    return self->capacity;
}

paxiword
pax_array_ring_head(Pax_Array_Ring* self)
{
    return self->length > 0 ? 0 : -1;
}

paxiword
pax_array_ring_tail(Pax_Array_Ring* self)
{
    return self->length > 0 ? self->length - 1 : -1;
}

paxb8
pax_array_ring_is_empty(Pax_Array_Ring* self)
{
    return self->length <= 0 ? 1 : 0;
}

paxb8
pax_array_ring_is_full(Pax_Array_Ring* self)
{
    return self->length >= self->capacity ? 1 : 0;
}

paxb8
pax_array_ring_insert_pure_head(Pax_Array_Ring* self, void* memory, paxiword stride)
{
    if (self->length < 0 || self->length >= self->capacity)
        return 0;

    if (self->stride != stride) return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, 0, self->capacity, stride);

    Pax_Slice value = pax_slice_make(memory, 0, 1, stride);

    paxiword index = self->head + self->capacity - 1;
    paxiword prev  = index;

    pax_slice_write(slice, prev % self->capacity, value);

    self->length += 1;
    self->head    = prev % self->capacity;

    return 1;
}

paxb8
pax_array_ring_insert_pure_tail(Pax_Array_Ring* self, void* memory, paxiword stride)
{
    if (self->length < 0 || self->length >= self->capacity)
        return 0;

    if (self->stride != stride) return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, 0, self->capacity, stride);

    Pax_Slice value = pax_slice_make(memory, 0, 1, stride);

    paxiword index = self->tail;
    paxiword next  = index + 1;

    pax_slice_write(slice, index % self->capacity, value);

    self->length += 1;
    self->tail    = next % self->capacity;

    return 1;
}

paxb8
pax_array_ring_remove_pure_head(Pax_Array_Ring* self, void* memory, paxiword stride)
{
    if (self->length <= 0 || self->length > self->capacity)
        return 0;

    if (self->stride != stride) return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, 0, self->capacity, stride);

    Pax_Slice value = pax_slice_make(memory, 0, 1, stride);

    paxiword index = self->head;
    paxiword next  = index + 1;

    pax_slice_read(slice, index % self->capacity, value);

    self->length -= 1;
    self->head    = next % self->capacity;

    return 1;
}

paxb8
pax_array_ring_remove_pure_tail(Pax_Array_Ring* self, void* memory, paxiword stride)
{
    if (self->length <= 0 || self->length > self->capacity)
        return 0;

    if (self->stride != stride) return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, 0, self->capacity, stride);

    Pax_Slice value = pax_slice_make(memory, 0, 1, stride);

    paxiword index = self->tail + self->capacity - 1;
    paxiword prev  = index;

    pax_slice_read(slice, index % self->capacity, value);

    self->length -= 1;
    self->tail    = prev % self->capacity;

    return 1;
}

paxb8
pax_array_ring_peek_pure(Pax_Array_Ring* self, paxiword index, void* memory, paxiword stride)
{
    if (index < 0 || index >= self->length || self->stride != stride)
        return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, 0, self->capacity, stride);

    Pax_Slice value = pax_slice_make(memory, 0, 1, stride);

    paxiword temp = self->head + index;

    pax_slice_read(slice, temp % self->capacity, value);

    return 1;
}

void*
pax_array_ring_peek_pure_or_null(Pax_Array_Ring* self, paxiword index)
{
    if (index < 0 || index >= self->length)
        return 0;

    paxiword temp = (self->head + index) % self->capacity;

    return &self->memory[temp * self->stride];
}

paxb8
pax_array_ring_update_pure(Pax_Array_Ring* self, paxiword index, void* memory, paxiword stride)
{
    if (index < 0 || index >= self->length || self->stride != stride)
        return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, 0, self->capacity, stride);

    Pax_Slice value = pax_slice_make(memory, 0, 1, stride);

    paxiword temp = self->head + index;

    pax_slice_write(slice, temp % self->capacity, value);

    return 1;
}

#endif // PAX_CORE_MEMORY_ARRAY_RING_C
