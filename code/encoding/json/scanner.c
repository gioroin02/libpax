#ifndef PAX_ENCODING_JSON_SCANNER_C
#define PAX_ENCODING_JSON_SCANNER_C

#include "./scanner.h"
#include "token.h"

static paxb8
pax_json_is_operator(paxu8 value)
{
    switch (value) {
        case PAX_ASCII_BRACE_LEFT:
        case PAX_ASCII_BRACE_RIGHT:
            return 1;

        case PAX_ASCII_SQUARE_LEFT:
        case PAX_ASCII_SQUARE_RIGHT:
            return 1;

        case PAX_ASCII_COMMA:
        case PAX_ASCII_COLON:
            return 1;

        default: break;
    }

    return 0;
}

static paxb8
pax_json_is_quote(paxb8 value)
{
    return value == PAX_ASCII_QUOTE ? 1 : 0;
}

static paxb8
pax_json_is_string(paxu8 value)
{
    return value != PAX_ASCII_QUOTE ? 1 : 0;
}

static paxb8
pax_json_is_number(paxu8 value)
{
    if (value >= PAX_ASCII_ZERO && value <= PAX_ASCII_NINE)
        return 1;

    switch (value) {
        case PAX_ASCII_PLUS:
        case PAX_ASCII_MINUS:
        case PAX_ASCII_POINT:
            return 1;

        case PAX_ASCII_UPPER_E:
        case PAX_ASCII_LOWER_E:
            return 1;

        default: break;
    }

    return 0;
}

static paxb8
pax_json_is_identifier(paxu8 value)
{
    if (value >= PAX_ASCII_ZERO && value <= PAX_ASCII_NINE)
        return 1;

    if (value >= PAX_ASCII_LOWER_A && value <= PAX_ASCII_LOWER_Z)
        return 1;

    if (value >= PAX_ASCII_UPPER_A && value <= PAX_ASCII_UPPER_Z)
        return 1;

    return 0;
}

paxu8
pax_source_drop_json_spaces(Pax_Scanner* self)
{
    paxu8 byte = 0;

    pax_scanner_drop_while(self, &pax_unicode_is_ascii_cntrl);

    if (pax_scanner_peek_memory8(self, 0, &byte, 1) <= 0)
        return 0;

    return byte;
}

Pax_JSON_Token
pax_scanner_read_json_operator(Pax_Scanner* self, Pax_Arena* arena, paxiword length)
{
    paxiword       mark   = pax_arena_tell(arena);
    Pax_JSON_Token result = pax_json_token_error();

    Pax_String8 string = pax_scanner_read_while(
        self, 0, arena, length, &pax_json_is_operator);

    if (string.length <= 0) return result;

    switch (string.memory[0]) {
        case PAX_ASCII_BRACE_LEFT:   result = pax_json_token_object_open();  break;
        case PAX_ASCII_BRACE_RIGHT:  result = pax_json_token_object_close(); break;
        case PAX_ASCII_SQUARE_LEFT:  result = pax_json_token_array_open();   break;
        case PAX_ASCII_SQUARE_RIGHT: result = pax_json_token_array_close();  break;
        case PAX_ASCII_COMMA:        result = pax_json_token_comma();        break;
        case PAX_ASCII_COLON:        result = pax_json_token_colon();        break;

        default: break;
    }

    pax_arena_rewind(arena, mark, 0);

    return result;
}

Pax_JSON_Token
pax_scanner_read_json_string(Pax_Scanner* self, Pax_Arena* arena, paxiword length)
{
    paxiword       mark   = pax_arena_tell(arena);
    Pax_JSON_Token result = pax_json_token_error();

    if (pax_scanner_drop_while(self, &pax_json_is_quote) != 1)
        return result;

    Pax_String8 string = pax_scanner_read_while(
        self, 0, arena, length, &pax_json_is_string);

    if (string.length <= 0) return result;

    if (pax_scanner_drop_while(self, &pax_json_is_quote) == 1)
        return pax_json_token_string(string);

    pax_arena_rewind(arena, mark, 0);

    return result;
}

Pax_JSON_Token
pax_scanner_read_json_number(Pax_Scanner* self, Pax_Arena* arena, paxiword length)
{
    paxiword       mark   = pax_arena_tell(arena);
    Pax_JSON_Token result = pax_json_token_error();

    Pax_String8 string = pax_scanner_read_while(
        self, 0, arena, length, &pax_json_is_number);

    if (string.length <= 0) return result;

    Pax_JSON_Token_Kind kind = PAX_JSON_TOKEN_KIND_UNSIGNED;

    for (paxiword i = 0; i < string.length; i += 1) {
        paxu8 byte = string.memory[i];

        switch (byte) {
            case PAX_ASCII_MINUS:
                if (kind == PAX_JSON_TOKEN_KIND_UNSIGNED)
                    kind = PAX_JSON_TOKEN_KIND_INTEGER;
            break;

            case PAX_ASCII_POINT:
            case PAX_ASCII_UPPER_E:
            case PAX_ASCII_LOWER_E:
                kind = PAX_JSON_TOKEN_KIND_FLOATING;
            break;

            default: break;
        }
    }

    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_PLUS;

    switch (kind) {
        case PAX_JSON_TOKEN_KIND_UNSIGNED: {
            paxuword value = 0;

            if (pax_unsigned_from_string8(string, &value, radix, flags) != 0)
                result = pax_json_token_unsigned(value);
        } break;

        case PAX_JSON_TOKEN_KIND_INTEGER: {
            paxiword value = 0;

            if (pax_integer_from_string8(string, &value, radix, flags) != 0)
                result = pax_json_token_integer(value);
        } break;

        case PAX_JSON_TOKEN_KIND_FLOATING: {
            paxfword value = 0;

            // if (pax_floating_from_string8(string, &value, radix, flags) != 0)
            //     result = pax_json_token_floating(value);
        } break;

        default: break;
    }

    pax_arena_rewind(arena, mark, 0);

    return result;
}

Pax_JSON_Token
pax_scanner_read_json_identifier(Pax_Scanner* self, Pax_Arena* arena, paxiword length)
{
    paxiword       mark   = pax_arena_tell(arena);
    Pax_JSON_Token result = pax_json_token_error();

    Pax_String8 string = pax_scanner_read_while(
        self, 0, arena, length, &pax_json_is_identifier);

    if (string.length <= 0) return result;

    if (pax_string8_is_equal(string, pax_str8("true")) != 0)
        result = pax_json_token_boolean(1);

    if (pax_string8_is_equal(string, pax_str8("false")) != 0)
        result = pax_json_token_boolean(0);

    if (pax_string8_is_equal(string, pax_str8("null")) != 0)
        result = pax_json_token_null();

    pax_arena_rewind(arena, mark, 0);

    return result;
}

Pax_JSON_Token
pax_scanner_read_json_token(Pax_Scanner* self, Pax_Arena* arena)
{
    Pax_JSON_Token result = pax_json_token_end();

    paxu8 byte = pax_source_drop_json_spaces(self);

    switch (byte) {
        case PAX_ASCII_NULL: return result;

        case PAX_ASCII_BRACE_LEFT:
        case PAX_ASCII_BRACE_RIGHT:
        case PAX_ASCII_SQUARE_LEFT:
        case PAX_ASCII_SQUARE_RIGHT:
        case PAX_ASCII_COMMA:
        case PAX_ASCII_COLON:
            result = pax_scanner_read_json_operator(
                self, arena, 1);
        break;

        case PAX_ASCII_QUOTE:
            result = pax_scanner_read_json_string(
                self, arena, PAX_MEMORY_KIB);
        break;

        case PAX_ASCII_PLUS:
        case PAX_ASCII_MINUS:
        case PAX_ASCII_ZERO:
        case PAX_ASCII_ONE:
        case PAX_ASCII_TWO:
        case PAX_ASCII_THREE:
        case PAX_ASCII_FOUR:
        case PAX_ASCII_FIVE:
        case PAX_ASCII_SIX:
        case PAX_ASCII_SEVEN:
        case PAX_ASCII_EIGHT:
        case PAX_ASCII_NINE:
            result = pax_scanner_read_json_number(
                self, arena, 64);
        break;

        case PAX_ASCII_LOWER_T:
        case PAX_ASCII_LOWER_F:
        case PAX_ASCII_LOWER_N:
            result = pax_scanner_read_json_identifier(
                self, arena, 16);
        break;

        default: break;
    }

    return result;
}

#endif // PAX_ENCODING_JSON_SCANNER_C
