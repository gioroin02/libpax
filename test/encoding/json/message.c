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
json_next_message(Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message message = {0};

    while (message.kind != PAX_JSON_MESSAGE_KIND_END) {
        paxiword mark = pax_arena_tell(arena);

        message = pax_json_reader_message(reader, arena);

        paxiword offset = pax_arena_tell(arena) - mark;

        printf("[%4lli + %4lli] ", mark, offset);

        if (message.kind == PAX_JSON_MESSAGE_KIND_END) break;

        switch (message.kind) {
            case PAX_JSON_MESSAGE_KIND_ERROR: {
                printf(RED("ERROR"));

                message.kind = PAX_JSON_MESSAGE_KIND_END;
            } break;

            case PAX_JSON_MESSAGE_KIND_OBJECT_OPEN:  printf("{"); break;
            case PAX_JSON_MESSAGE_KIND_OBJECT_CLOSE: printf("}"); break;
            case PAX_JSON_MESSAGE_KIND_ARRAY_OPEN:   printf("["); break;
            case PAX_JSON_MESSAGE_KIND_ARRAY_CLOSE:  printf("]"); break;

            case PAX_JSON_MESSAGE_KIND_NAME:
                printf(CYA("'%s'"), message.name.memory);
            break;

            case PAX_JSON_MESSAGE_KIND_STRING: {
                if (message.name.length > 0)
                    printf(CYA("'%s'") ": ", message.name.memory);

                printf(BLU("'%s'"), message.value_string.memory);
            } break;

            case PAX_JSON_MESSAGE_KIND_UNSIGNED: {
                if (message.name.length > 0)
                    printf(CYA("'%s'") ": ", message.name.memory);

                printf(MAG("%llu"), message.value_unsigned);
            } break;

            case PAX_JSON_MESSAGE_KIND_INTEGER: {
                if (message.name.length > 0)
                    printf(CYA("'%s'") ": ", message.name.memory);

                printf(MAG("%lli"), message.value_integer);
            } break;

            case PAX_JSON_MESSAGE_KIND_FLOATING: {
                if (message.name.length > 0)
                    printf(CYA("'%s'") ": ", message.name.memory);

                printf(MAG("%lf"), message.value_floating);
            } break;

            case PAX_JSON_MESSAGE_KIND_BOOLEAN: {
                if (message.name.length > 0)
                    printf(CYA("'%s'") ": ", message.name.memory);

                printf("%s", message.value_boolean != 0 ? GRN("true") : RED("false"));
            } break;

            case PAX_JSON_MESSAGE_KIND_NULL: {
                if (message.name.length > 0)
                    printf(CYA("'%s'") ": ", message.name.memory);

                printf(YLW("null"));
            } break;

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

    Pax_JSON_Reader reader = pax_json_reader_create(&arena, 16, scanner);

    json_next_message(&reader, &arena);
}
