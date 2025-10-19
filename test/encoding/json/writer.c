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

paxb8
entity_flags_json_write(Entity_Flag* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    static const Pax_String8 names[] = {
        pax_str8("shown"),
        pax_str8("alive"),
    };

    pax_json_writer_array_open(writer, arena);

    for (paxiword i = 0; i < 2; i += 1) {
        if ((*self & (1 << i)) == 0) continue;

        pax_json_writer_message(writer, arena,
            pax_json_message_string(names[i]));
    }

    pax_json_writer_array_close(writer, arena);

    return 1;
}

paxb8
entity_tags_json_write(Entity_Tags* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    pax_json_writer_array_open(writer, arena);

    for (paxiword i = 0; i < self->size; i += 1)
        pax_json_writer_message(writer, arena, pax_json_message_string(self->items[i]));

    pax_json_writer_array_close(writer, arena);

    return 1;
}

paxb8
entity_json_write(Entity* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    pax_json_writer_object_open(writer, arena);

    Pax_JSON_Message parent = pax_json_message_null();

    if (self->parent != 0)
        parent = pax_json_message_unsigned(self->parent);

    pax_json_writer_many(writer, arena, (Pax_JSON_Message[]) {
        pax_json_message_pair(pax_str8("parent"), parent),
        pax_json_message_pair(pax_str8("name"),  pax_json_message_string(self->name)),
        pax_json_message_pair(pax_str8("code"),  pax_json_message_unsigned(self->code)),
        pax_json_message_pair(pax_str8("flags"), pax_json_message_delegate(&self->tags, &entity_flags_json_write)),
        pax_json_message_pair(pax_str8("tags"),  pax_json_message_delegate(&self->tags, &entity_tags_json_write)),
    }, 5);

    pax_json_writer_object_close(writer, arena);

    return 1;
}

int
main(int argc, char** argv)
{
    Pax_Arena   arena  = pax_memory_reserve(16);
    Pax_Buffer8 buffer = pax_buffer8_create(&arena, 256);
    Pax_Target* target = pax_target_from_buffer8(&arena, &buffer);

    Pax_JSON_Writer writer = pax_json_writer_create(&arena, 16, target);

    Entity entity = {
        .name  = pax_str8("Charred sword"),
        .code  = 156,
        .flags = ENTITY_ALIVE,
        .tags  = {
            .items = {
                pax_str8("element:fire"),
                pax_str8("damage:slashing"),
                pax_str8("damage:draconic"),
            },
            .size = 3
        }
    };

    entity_show(&entity, 0);

    entity_json_write(&entity, &writer, &arena);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        pax_as(int, buffer.length), buffer.memory);
}
