#ifndef PAX_CORE_STRING_BUFFER8_C
#define PAX_CORE_STRING_BUFFER8_C

#include "buffer8.h"

Pax_Buffer8
pax_buffer8_make(paxu8* memory, paxiword length)
{
    return pax_array_make(paxu8, memory, length);
}

Pax_Buffer8
pax_buffer8_create(Pax_Arena* arena, paxiword length)
{
    return pax_array_create(arena, paxu8, length);
}

void
pax_buffer8_clear(Pax_Buffer8* self)
{
    pax_array_clear(self);
}

void
pax_buffer8_fill(Pax_Buffer8* self)
{
    pax_array_fill(self);
}

paxiword
pax_buffer8_length(Pax_Buffer8* self)
{
    return pax_array_length(self);
}

paxiword
pax_buffer8_capacity(Pax_Buffer8* self)
{
    return pax_array_capacity(self);
}

paxiword
pax_buffer8_head(Pax_Buffer8* self)
{
    return pax_array_head(self);
}

paxiword
pax_buffer8_tail(Pax_Buffer8* self)
{
    return pax_array_tail(self);
}

paxiword
pax_buffer8_drop_head(Pax_Buffer8* self, paxiword length)
{
    paxiword index = pax_array_head(self);

    return pax_array_remove(self, paxu8,
        index, 0, length);
}

paxiword
pax_buffer8_drop_tail(Pax_Buffer8* self, paxiword length)
{
    paxiword index = pax_array_tail(self);

    return pax_array_remove(self, paxu8,
        index, 0, length);
}

paxiword
pax_buffer8_write_head_memory8(Pax_Buffer8* self, paxu8* memory, paxiword length)
{
    paxiword index = pax_array_head(self);

    return pax_array_insert(self, paxu8,
        index, memory, length);
}

paxiword
pax_buffer8_write_head_buffer8(Pax_Buffer8* self, Pax_Buffer8* value)
{
    paxu8*   memory = value->memory;
    paxiword length = value->length;

    paxiword size = pax_buffer8_write_head_memory8(self, memory, length);

    pax_buffer8_drop_head(value, size);

    return size;
}

paxiword
pax_buffer8_write_tail_memory8(Pax_Buffer8* self, paxu8* memory, paxiword length)
{
    paxiword index = pax_array_tail(self);

    return pax_array_insert(self,
        paxu8, index + 1, memory, length);
}

paxiword
pax_buffer8_write_tail_buffer8(Pax_Buffer8* self, Pax_Buffer8* value)
{
    paxu8*   memory = value->memory;
    paxiword length = value->length;

    paxiword size = pax_buffer8_write_tail_memory8(self, memory, length);

    pax_buffer8_drop_head(value, size);

    return size;
}

paxiword
pax_buffer8_read_head_memory8(Pax_Buffer8* self, paxu8* memory, paxiword length)
{
    paxiword index = pax_array_head(self);

    return pax_array_remove(self,
        paxu8, index, memory, length);
}

paxiword
pax_buffer8_read_head_buffer8(Pax_Buffer8* self, Pax_Buffer8* value)
{
    paxu8*   memory = value->memory   + value->length;
    paxiword length = value->capacity - value->length;

    paxiword size = pax_buffer8_read_head_memory8(self, memory, length);

    value->length += size;

    return size;
}

paxiword
pax_buffer8_read_tail_memory8(Pax_Buffer8* self, paxu8* memory, paxiword length)
{
    paxiword index = pax_array_tail(self);

    return pax_array_remove(self,
        paxu8, index - length, memory, length);
}

paxiword
pax_buffer8_read_tail_buffer8(Pax_Buffer8* self, Pax_Buffer8* value)
{
    paxu8*   memory = value->memory   + value->length;
    paxiword length = value->capacity - value->length;

    paxiword size = pax_buffer8_read_tail_memory8(self, memory, length);

    value->length += size;

    return size;
}

paxiword
pax_buffer8_peek_memory8(Pax_Buffer8* self, paxiword index, paxu8* memory, paxiword length)
{
    return pax_array_peek(self, paxu8, index, memory, length);
}

paxiword
pax_buffer8_peek_buffer8(Pax_Buffer8* self, paxiword index, Pax_Buffer8* value)
{
    paxu8*   memory = value->memory   + value->length;
    paxiword length = value->capacity - value->length;

    paxiword size = pax_buffer8_peek_memory8(self, index, memory, length);

    value->length += size;

    return size;
}

paxu8
pax_buffer8_peek_or_none(Pax_Buffer8* self, paxiword index)
{
    paxu8 result = 0;

    if (pax_array_peek(self, paxu8, index, &result, 1) != 0)
        return result;

    return 0;
}

#endif // PAX_CORE_STRING_BUFFER8_C
