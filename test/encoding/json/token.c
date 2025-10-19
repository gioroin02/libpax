#include "../../../code/encoding/json/export.h"

#include <stdio.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

#define ENTITY \
    pax_str8("{\n\t\"flags\": [16, 32],\n\t\"code\": 156,\n\t\"name\": \"player\",\n\t\"coords\": {\"x\": -1, \"y\": +2, \"z\": null},\n\t\"alive\": true,\n\t\"pause\": false\n}")

void
json_next_token(Pax_Scanner* self, Pax_Arena* arena)
{
    Pax_JSON_Token token = {0};

    while (token.kind != PAX_JSON_TOKEN_KIND_END) {
        paxiword mark = pax_arena_tell(arena);

        token = pax_scanner_read_json_token(self, arena);

        paxiword offset = pax_arena_tell(arena) - mark;

        printf("[%4lli + %4lli] ", mark, offset);

        switch (token.kind) {
            case PAX_JSON_TOKEN_KIND_ERROR: {
                printf(RED("ERROR"));

                token.kind = PAX_JSON_TOKEN_KIND_END;
            } break;

            case PAX_JSON_TOKEN_KIND_OBJECT_OPEN:  printf("{");         break;
            case PAX_JSON_TOKEN_KIND_OBJECT_CLOSE: printf("}");         break;
            case PAX_JSON_TOKEN_KIND_ARRAY_OPEN:   printf("[");         break;
            case PAX_JSON_TOKEN_KIND_ARRAY_CLOSE:  printf("]");         break;
            case PAX_JSON_TOKEN_KIND_COMMA:        printf(",");         break;
            case PAX_JSON_TOKEN_KIND_COLON:        printf(":");         break;
            case PAX_JSON_TOKEN_KIND_NULL:         printf(YLW("null")); break;

            case PAX_JSON_TOKEN_KIND_STRING:
                printf(BLU("'%s'"), token.value_string.memory);
            break;

            case PAX_JSON_TOKEN_KIND_UNSIGNED:
                printf(MAG("%llu"), token.value_unsigned);
            break;

            case PAX_JSON_TOKEN_KIND_INTEGER:
                printf(MAG("%lli"), token.value_integer);
            break;

            case PAX_JSON_TOKEN_KIND_FLOATING:
                printf(MAG("%lf"), token.value_floating);
            break;

            case PAX_JSON_TOKEN_KIND_BOOLEAN:
                printf("%s", token.value_boolean != 0 ? GRN("true") : RED("false"));
            break;

            default: break;
        }

        printf("\n");
    }
}

int
main(int argc, char** argv)
{
    Pax_Arena   arena  = pax_memory_reserve(16);
    Pax_Buffer8 buffer = pax_buffer8_create(&arena, 256);

    pax_buffer8_write_tail_string8(&buffer, ENTITY);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        pax_as(int, buffer.length), buffer.memory);

    printf("\n");

    Pax_Scanner scanner = pax_scanner_create(&arena, 1,
        pax_source_from_buffer8(&arena, &buffer));

    json_next_token(&scanner, &arena);
}
