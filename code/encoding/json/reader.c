#ifndef PAX_ENCODING_JSON_READER_C
#define PAX_ENCODING_JSON_READER_C

#include "./reader.h"
#include "scanner.c"

Pax_JSON_Reader
pax_json_reader_create(Pax_Arena* arena, paxiword length, Pax_Scanner scanner)
{
    return (Pax_JSON_Reader) {
        .stack   = pax_array_ring_create(arena, Pax_JSON_Layer_Kind, length),
        .scanner = scanner,
    };
}

Pax_JSON_Message
pax_json_reader_message(Pax_JSON_Reader* self, Pax_Arena* arena)
{
    Pax_JSON_Message    result = pax_json_message_end();
    Pax_JSON_Layer_Kind parent = PAX_JSON_LAYER_KIND_NONE;

    while (result.kind == PAX_JSON_MESSAGE_KIND_END) {
        paxiword index = pax_array_ring_tail(&self->stack);

        pax_array_ring_peek(&self->stack, Pax_JSON_Layer_Kind, index, &parent, 1);

        Pax_JSON_Token token = self->token;

        self->token = (Pax_JSON_Token) {0};

        if (token.kind == PAX_JSON_TOKEN_KIND_NONE)
            token = pax_scanner_read_json_token(&self->scanner, arena);

        if (token.kind == PAX_JSON_TOKEN_KIND_END) break;

        switch (token.kind) {
            case PAX_JSON_TOKEN_KIND_ERROR: {
                result = pax_json_message_error();
            } break;

            case PAX_JSON_TOKEN_KIND_OBJECT_OPEN: {
                result = pax_json_message_object_open();

                Pax_JSON_Layer_Kind layer = PAX_JSON_LAYER_KIND_OBJECT;

                pax_array_ring_insert_tail(&self->stack,
                    Pax_JSON_Layer_Kind, &layer, 1);

                self->name   = (Pax_String8) {0};
                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_OBJECT_CLOSE: {
                result = pax_json_message_object_close();

                pax_array_ring_remove_tail(&self->stack,
                    Pax_JSON_Layer_Kind, 0, 1);

                self->name   = (Pax_String8) {0};
                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_ARRAY_OPEN: {
                result = pax_json_message_array_open();

                Pax_JSON_Layer_Kind layer = PAX_JSON_LAYER_KIND_ARRAY;

                pax_array_ring_insert_tail(&self->stack,
                    Pax_JSON_Layer_Kind, &layer, 1);

                self->name   = (Pax_String8) {0};
                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_ARRAY_CLOSE: {
                result = pax_json_message_array_close();

                pax_array_ring_remove_tail(&self->stack,
                    Pax_JSON_Layer_Kind, 0, 1);

                self->name   = (Pax_String8) {0};
                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_COLON: {
                if (parent == PAX_JSON_LAYER_KIND_ARRAY)
                    result = pax_json_message_error();

                if (parent == PAX_JSON_LAYER_KIND_OBJECT) {
                    self->token = pax_scanner_read_json_token(&self->scanner, arena);

                    switch (self->token.kind) {
                        case PAX_JSON_TOKEN_KIND_OBJECT_OPEN:
                        case PAX_JSON_TOKEN_KIND_ARRAY_OPEN:
                            result = pax_json_message_name(self->name);
                        break;

                        default: break;
                    }
                }

                self->flags |=  PAX_JSON_READER_COLON;
                self->flags &= ~PAX_JSON_READER_COMMA;
            } break;

            case PAX_JSON_TOKEN_KIND_COMMA: {
                self->name   = (Pax_String8) {0};
                self->flags &= ~PAX_JSON_READER_COLON;
                self->flags |=  PAX_JSON_READER_COMMA;
            } break;

            case PAX_JSON_TOKEN_KIND_STRING: {
                paxb8 colon = (self->flags & PAX_JSON_READER_COLON) != 0;

                if (parent != PAX_JSON_LAYER_KIND_OBJECT || colon != 0) {
                    result = pax_json_message_string(token.value_string);

                    if (self->name.length > 0)
                        result = pax_json_message_pair(self->name, result);
                } else
                    self->name = token.value_string;

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_UNSIGNED: {
                result = pax_json_message_unsigned(token.value_unsigned);

                if (self->name.length > 0)
                    result = pax_json_message_pair(self->name, result);

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_INTEGER: {
                result = pax_json_message_integer(token.value_integer);

                if (self->name.length > 0)
                    result = pax_json_message_pair(self->name, result);

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_FLOATING: {
                result = pax_json_message_floating(token.value_floating);

                if (self->name.length > 0)
                    result = pax_json_message_pair(self->name, result);

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_BOOLEAN: {
                result = pax_json_message_boolean(token.value_boolean);

                if (self->name.length > 0)
                    result = pax_json_message_pair(self->name, result);

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_NULL: {
                result = pax_json_message_null();

                if (self->name.length > 0)
                    result = pax_json_message_pair(self->name, result);

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            default: break;
        }
    }

    if (result.name.length > 0) self->name = (Pax_String8) {0};

    return result;
}

paxb8
pax_json_reader_object(Pax_JSON_Reader* self, Pax_Arena* arena, void* ctxt, void* proc)
{
    if (proc == 0) return 0;

    Pax_JSON_Message message = pax_json_reader_message(self, arena);

    if (message.kind != PAX_JSON_MESSAGE_KIND_OBJECT_OPEN)
        return 0;

    message = pax_json_reader_message(self, arena);

    while (message.kind != PAX_JSON_MESSAGE_KIND_OBJECT_CLOSE) {
        if (message.kind == PAX_JSON_MESSAGE_KIND_END) break;

        if (message.name.length > 0)
            pax_as(Pax_JSON_Reader_Proc*, proc)(ctxt, message, self, arena);

        message = pax_json_reader_message(self, arena);
    }

    return 1;
}

paxb8
pax_json_reader_array(Pax_JSON_Reader* self, Pax_Arena* arena, void* ctxt, void* proc)
{
    if (proc == 0) return 0;

    Pax_JSON_Message message = pax_json_reader_message(self, arena);

    if (message.kind != PAX_JSON_MESSAGE_KIND_ARRAY_OPEN)
        return 0;

    message = pax_json_reader_message(self, arena);

    while (message.kind != PAX_JSON_MESSAGE_KIND_ARRAY_CLOSE) {
        if (message.kind == PAX_JSON_MESSAGE_KIND_END) break;

        if (message.name.length <= 0)
           pax_as(Pax_JSON_Reader_Proc*, proc)(ctxt, message, self, arena);

        message = pax_json_reader_message(self, arena);
    }

    return 1;
}

#endif // PAX_ENCODING_JSON_READER_C
