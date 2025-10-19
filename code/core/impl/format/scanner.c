#ifndef PAX_CORE_FORMAT_SCANNER_C
#define PAX_CORE_FORMAT_SCANNER_C

#include "./scanner.h"

Pax_Scanner
pax_scanner_create(Pax_Arena* arena, paxiword length, Pax_Source* source)
{
    if (source == 0) return (Pax_Scanner) {0};

    return (Pax_Scanner) {
        .buffer = pax_buffer8_create(arena, length),
        .source = source,
    };
}

paxiword
pax_scanner_drop(Pax_Scanner* self, paxiword length)
{
    paxiword size = 0;
    paxiword temp = 1;

    for (; size < length && temp > 0; size += temp) {
        if (pax_buffer8_length(&self->buffer) <= 0)
            pax_source_read_buffer8(self->source, &self->buffer);

        temp = pax_buffer8_drop_head(&self->buffer, length - size);
    }

    return size;
}

paxiword
pax_scanner_drop_while(Pax_Scanner* self, void* proc)
{
    if (proc == 0) return 0;

    paxiword size = 0;

    for (; 1; size += 1) {
        paxu8 byte = 0;

        paxiword temp = pax_scanner_peek_memory8(self, 0, &byte, 1);

        if (temp <= 0 || byte == 0) break;

        if (pax_as(Pax_Scanner_Proc*, proc)(byte) == 0)
            break;

        pax_scanner_drop(self, 1);
    }

    return size;
}

paxiword
pax_scanner_drop_until(Pax_Scanner* self, void* proc)
{
    if (proc == 0) return 0;

    paxiword size = 0;

    for (; 1; size += 1) {
        paxu8 byte = 0;

        paxiword temp = pax_scanner_peek_memory8(self, 0, &byte, 1);

        if (temp <= 0 || byte == 0) break;

        if (pax_as(Pax_Scanner_Proc*, proc)(byte) != 0)
            break;

        pax_scanner_drop(self, 1);
    }

    return size;
}

paxiword
pax_scanner_read_memory8(Pax_Scanner* self, paxiword offset, paxu8* memory, paxiword length)
{
    paxiword size = 0;
    paxiword temp = 1;

    if (pax_scanner_drop(self, offset) < offset) return 0;

    for (; size < length && temp > 0; size += temp) {
        if (pax_buffer8_length(&self->buffer) <= 0)
            pax_source_read_buffer8(self->source, &self->buffer);

        temp = pax_buffer8_read_head_memory8(&self->buffer,
            memory + size, length - size);
    }

    return size;
}

Pax_String8
pax_scanner_read_while(Pax_Scanner* self, paxiword offset, Pax_Arena* arena, paxiword length, void* proc)
{
    if (pax_scanner_drop(self, offset) < offset)
        return (Pax_String8) {0};

    if (length <= 0 || proc == 0) return (Pax_String8) {0};

    paxiword mark   = pax_arena_tell(arena);
    paxu8*   memory = pax_arena_reserve(arena, paxu8, length + 1);

    paxiword size = 0;

    for (; size < length; size += 1) {
        paxu8 byte = 0;

        paxiword temp = pax_scanner_peek_memory8(self, 0, &byte, 1);

        if (temp <= 0 || byte == 0) break;

        if (pax_as(Pax_Scanner_Proc*, proc)(byte) == 0)
            break;

        memory[size] = byte;

        pax_scanner_drop(self, 1);
    }

    if (size > 0 && size <= length) {
        Pax_String8 string =
            pax_string8_make(memory, size);

        pax_arena_rewind(arena, mark, size + 1);

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

Pax_String8
pax_scanner_read_until(Pax_Scanner* self, paxiword offset, Pax_Arena* arena, paxiword length, void* proc)
{
    if (pax_scanner_drop(self, offset) < offset)
        return (Pax_String8) {0};

    if (length <= 0 || proc == 0) return (Pax_String8) {0};

    paxiword mark   = pax_arena_tell(arena);
    paxu8*   memory = pax_arena_reserve(arena, paxu8, length + 1);

    paxiword size = 0;

    for (; size < length; size += 1) {
        paxu8 byte = 0;

        paxiword temp = pax_scanner_peek_memory8(self, 0, &byte, 1);

        if (temp <= 0 || byte == 0) break;

        if (pax_as(Pax_Scanner_Proc*, proc)(byte) != 0)
            break;

        memory[size] = byte;

        pax_scanner_drop(self, 1);
    }

    if (size > 0 && size <= length) {
        Pax_String8 string =
            pax_string8_make(memory, size);

        pax_arena_rewind(arena, mark, size + 1);

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

paxiword
pax_scanner_peek_memory8(Pax_Scanner* self, paxiword offset, paxu8* memory, paxiword length)
{
    paxiword size = 0;
    paxiword temp = 1;

    if (offset < 0) return 0;

    for (; size < length && temp > 0; size += temp) {
        if (pax_buffer8_length(&self->buffer) <= 0)
            pax_source_read_buffer8(self->source, &self->buffer);

        if (offset + size >= pax_buffer8_length(&self->buffer))
            break;

        temp = pax_buffer8_peek_memory8(&self->buffer,
            offset + size, memory + size, length - size);
    }

    return size;
}

Pax_String8
pax_scanner_peek_while(Pax_Scanner* self, paxiword offset, Pax_Arena* arena, paxiword length, void* proc)
{
    if (length <= 0 || proc == 0) return (Pax_String8) {0};

    paxiword mark   = pax_arena_tell(arena);
    paxu8*   memory = pax_arena_reserve(arena, paxu8, length + 1);

    paxiword size = 0;

    for (; size < length; size += 1) {
        paxu8 byte = 0;

        paxiword temp = pax_scanner_peek_memory8(self,
            offset + size, &byte, 1);

        if (temp <= 0 || byte == 0) break;

        if (pax_as(Pax_Scanner_Proc*, proc)(byte) == 0)
            break;

        memory[size] = byte;
    }

    if (size > 0 && size <= length) {
        Pax_String8 string =
            pax_string8_make(memory, size);

        pax_arena_rewind(arena, mark, size + 1);

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

Pax_String8
pax_scanner_peek_until(Pax_Scanner* self, paxiword offset, Pax_Arena* arena, paxiword length, void* proc)
{
    if (length <= 0 || proc == 0) return (Pax_String8) {0};

    paxiword mark   = pax_arena_tell(arena);
    paxu8*   memory = pax_arena_reserve(arena, paxu8, length + 1);

    paxiword size = 0;

    for (; size < length; size += 1) {
        paxu8 byte = 0;

        paxiword temp = pax_scanner_peek_memory8(self,
            offset + size, &byte, 1);

        if (temp <= 0 || byte == 0) break;

        if (pax_as(Pax_Scanner_Proc*, proc)(byte) != 0)
            break;

        memory[size] = byte;
    }

    if (size > 0 && size <= length) {
        Pax_String8 string =
            pax_string8_make(memory, size);

        pax_arena_rewind(arena, mark, size + 1);

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

#endif // PAX_CORE_FORMAT_SCANNER_C
