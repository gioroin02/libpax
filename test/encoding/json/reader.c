#include "../../../code/encoding/json/export.h"

#include <stdio.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

typedef Pax_String8 Entity_Tag;

#define ENTITY_TAGS_ITEMS pax_as(paxiword, 16)

typedef struct Entity_Tags
{
    Entity_Tag items[ENTITY_TAGS_ITEMS];
    paxiword   size;
}
Entity_Tags;

typedef enum Entity_Flag
{
    ENTITY_NONE  = 0,
    ENTITY_SHOWN = 1 << 0,
    ENTITY_ALIVE = 1 << 1,
}
Entity_Flag;

typedef struct Entity
{
    paxuword parent;

    Pax_String8 name;
    paxuword    code;

    Entity_Flag flags;
    Entity_Tags tags;
}
Entity;

void
indent_show(paxiword level)
{
    level = pax_min(level, 1);

    for (paxiword i = 0; i <= level; i += 1)
        printf("%4c", PAX_ASCII_SPACE);
}

void
entity_flags_show(Entity_Flag* self, paxiword level)
{
    static const Pax_String8 names[] = {
        pax_str8("shown"),
        pax_str8("alive"),
    };

    printf("(Entity_Flags) {\n");

    for (paxiword i = 0; i < 2; i += 1) {
        indent_show(level);

        printf("[%s] = %i\n", names[i].memory, *self & (1 << i));
    }

    indent_show(level - 1);

    printf("}\n");
}

void
entity_tags_show(Entity_Tags* self, paxiword level)
{
    printf("(Entity_Tags) {\n");

    for (paxiword i = 0; i < self->size; i += 1) {
        indent_show(level);

        printf("[%lli] = '%s'\n",
            i, self->items[i].memory);
    }

    indent_show(level - 1);

    printf("}\n");
}

void
entity_show(Entity* self, paxiword level)
{
    printf("(Entity) {\n");

    indent_show(level);

    printf("[.parent] = %llu\n", self->parent);

    indent_show(level);

    printf("[.name] = '%.*s'\n",
        pax_as(int, self->name.length), self->name.memory);

    indent_show(level);

    printf("[.code] = %llu\n", self->code);

    indent_show(level);

    printf("[.flags] = ");

    entity_flags_show(&self->flags, level + 1);

    indent_show(level);

    printf("[.tags] = ");

    entity_tags_show(&self->tags, level + 1);

    indent_show(level - 1);

    printf("}\n");
}

void
entity_flags_json_read(Entity_Flag* self, Pax_JSON_Message message, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    switch (message.kind) {
        case PAX_JSON_MESSAGE_KIND_STRING: {
            if (pax_string8_is_equal(message.value_string, pax_str8("shown")) != 0)
                *self |= ENTITY_SHOWN;

            if (pax_string8_is_equal(message.value_string, pax_str8("alive")) != 0)
                *self |= ENTITY_ALIVE;
        } break;

        default: break;
    }
}

void
entity_tags_json_read(Entity_Tags* self, Pax_JSON_Message message, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    if (self->size < 0 || self->size >= ENTITY_TAGS_ITEMS)
        return;

    switch (message.kind) {
        case PAX_JSON_MESSAGE_KIND_STRING:
            if (message.value_string.length <= 0)
                break;

            paxiword index = self->size;

            self->size += 1;

            self->items[index] =
                message.value_string;
        break;

        default: break;
    }
}

void
entity_json_read(Entity* self, Pax_JSON_Message message, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    switch (message.kind) {
        case PAX_JSON_MESSAGE_KIND_NAME: {
            if (pax_string8_is_equal(message.name, pax_str8("flags")) != 0)
                pax_json_reader_array(reader, arena, &self->flags, &entity_flags_json_read);

            if (pax_string8_is_equal(message.name, pax_str8("tags")) != 0)
                pax_json_reader_array(reader, arena, &self->tags, &entity_tags_json_read);
        } break;

        case PAX_JSON_MESSAGE_KIND_STRING: {
            if (pax_string8_is_equal(message.name, pax_str8("name")) != 0)
                self->name = message.value_string;
        } break;

        case PAX_JSON_MESSAGE_KIND_UNSIGNED: {
            if (pax_string8_is_equal(message.name, pax_str8("parent")) != 0)
                self->parent = message.value_unsigned;

            if (pax_string8_is_equal(message.name, pax_str8("code")) != 0)
                self->code = message.value_unsigned;
        } break;

        default: break;
    }
}

#define ENTITY pax_str8( \
    "{\"parent\":null,\"name\":\"Charred sword\",\"code\":156,\"flags\":[\"alive\"],\"tags\":[\"element:fire\",\"damage:slashing\",\"damage:draconic\"]}" \
)

int
main(int argc, char** argv)
{
    Pax_Arena   arena  = pax_memory_reserve(16);
    Pax_Buffer8 buffer = pax_buffer8_create(&arena, 256);

    Entity entity = {0};

    pax_buffer8_write_tail_string8(&buffer, ENTITY);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        pax_as(int, buffer.length), buffer.memory);

    printf("\n");

    Pax_Scanner scanner = pax_scanner_create(&arena, 1,
        pax_source_from_buffer8(&arena, &buffer));

    Pax_JSON_Reader reader = pax_json_reader_create(&arena, 16, scanner);

    pax_json_reader_object(&reader, &arena, &entity, &entity_json_read);

    entity_show(&entity, 0);
}
