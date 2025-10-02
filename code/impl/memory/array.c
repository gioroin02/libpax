#ifndef PAX_CORE_MEMORY_ARRAY_C
#define PAX_CORE_MEMORY_ARRAY_C

#include "array.h"

Pax_Array
pax_array_create_pure(Pax_Arena* arena, paxiword length, paxiword stride)
{
    Pax_Array result = {0};

    Pax_Slice slice =
        pax_arena_reserve_slice(arena, length, stride);

    result.memory   = slice.memory;
    result.stride   = slice.stride;
    result.capacity = slice.length;

    return result;
}

Pax_Array
pax_array_copy(Pax_Arena* arena, Pax_Array* value)
{
    Pax_Array result =
        pax_array_create_pure(arena, value->length, value->stride);

    if (result.capacity == 0) return result;

    Pax_Slice left  = pax_array_slice(&result, 0, result.capacity);
    Pax_Slice right = pax_array_slice(value,   0, result.capacity);

    pax_slice_copy(left, right);

    return result;
}

Pax_Slice
pax_array_slice(Pax_Array* self, paxiword start, paxiword stop)
{
    Pax_Slice result = {0};

    start = pax_between(start, 0, self->length);
    stop  = pax_between(stop,  0, self->length);

    result = pax_slice_make(self->memory,
        start, stop, self->stride);

    return result;
}

Pax_Slice
pax_array_slice_amount(Pax_Array* self, paxiword index, paxiword amount)
{
    return pax_array_slice(self, index, index + amount);
}

void
pax_array_clear(Pax_Array* self)
{
    self->length = 0;
}

void
pax_array_fill(Pax_Array* self)
{
    Pax_Slice slice = pax_slice_make(self->memory,
        self->length, self->capacity, self->stride);

    pax_slice_zero(slice);

    self->length = self->capacity;
}

paxiword
pax_array_length(Pax_Array* self)
{
    return self->length;
}

paxiword
pax_array_capacity(Pax_Array* self)
{
    return self->capacity;
}

paxiword
pax_array_head(Pax_Array* self)
{
    return self->length > 0 ? 0 : -1;
}

paxiword
pax_array_tail(Pax_Array* self)
{
    return self->length > 0 ? self->length - 1 : -1;
}

paxb8
pax_array_is_empty(Pax_Array* self)
{
    return self->length <= 0 ? 1 : 0;
}

paxb8
pax_array_is_full(Pax_Array* self)
{
    return self->length >= self->capacity ? 1 : 0;
}

paxb8
pax_array_insert_pure(Pax_Array* self, paxiword index, void* memory, paxiword stride)
{
    if (self->length < 0 || self->length >= self->capacity)
        return 0;

    if (index < 0 || index > self->length || self->stride != stride)
        return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, 0, self->capacity, stride);

    Pax_Slice value = pax_slice_make(memory, 0, 1, stride);

    if (index < self->length)
        pax_slice_shift_forw(slice, index, self->length - index, 1);

    self->length += 1;

    pax_slice_write(slice, index, value);

    return 1;
}

paxb8
pax_array_remove_pure(Pax_Array* self, paxiword index, void* memory, paxiword stride)
{
    if (index < 0 || index >= self->length || self->stride != stride)
        return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, 0, self->capacity, stride);

    Pax_Slice value = pax_slice_make(memory, 0, 1, stride);

    pax_slice_read(slice, index, value);

    self->length -= 1;

    if (index < self->length)
        pax_slice_shift_back(slice, index, self->length - index, 1);

    return 1;
}

paxb8
pax_array_peek_pure(Pax_Array* self, paxiword index, void* memory, paxiword stride)
{
    if (index < 0 || index >= self->length || self->stride != stride)
        return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, 0, self->capacity, stride);

    Pax_Slice value = pax_slice_make(memory, 0, 1, stride);

    pax_slice_read(slice, index, value);

    return 1;
}

void*
pax_array_peek_pure_or_null(Pax_Array* self, paxiword index)
{
    if (index < 0 || index >= self->length)
        return 0;

    return &self->memory[index * self->stride];
}

paxb8
pax_array_update_pure(Pax_Array* self, paxiword index, void* memory, paxiword stride)
{
    if (index < 0 || index >= self->length || self->stride != stride)
        return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, 0, self->capacity, stride);

    Pax_Slice value = pax_slice_make(memory, 0, 1, stride);

    pax_slice_write(slice, index, value);

    return 1;
}

#endif // PAX_CORE_MEMORY_ARRAY_C
