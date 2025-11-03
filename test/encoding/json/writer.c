#include "../../../code/encoding/json/export.h"

#include <stdio.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

typedef enum Entity_Kind
{
    ENTITY_KIND_NONE,
    ENTITY_KIND_DECOR,
    ENTITY_KIND_ITEM,
}
Entity_Kind;

#define ENTITY_DECOR_TAGS_ITEMS pax_as(paxiword, 16)

typedef struct Entity_Decor_Tags
{
    Pax_String8 items[ENTITY_DECOR_TAGS_ITEMS];
    paxiword    size;
}
Entity_Decor_Tags;

typedef struct Entity_Decor
{
    paxiword world_x;
    paxiword world_y;

    Pax_String8 name;

    Entity_Decor_Tags tags;
}
Entity_Decor;

typedef enum Entity_Item_Flag
{
    ENTITY_ITEM_FLAG_NONE  = 0,
    ENTITY_ITEM_FLAG_COUNT = 5,

    ENTITY_ITEM_FLAG_SHOWN = 1 << 0,
    ENTITY_ITEM_FLAG_ALIVE = 1 << 1,
    ENTITY_ITEM_FLAG_SOLID = 1 << 2,
    ENTITY_ITEM_FLAG_FLUID = 1 << 3,
    ENTITY_ITEM_FLAG_FOOD  = 1 << 4,
}
Entity_Item_Flag;

typedef struct Entity_Item
{
    paxiword    parent;
    Pax_String8 name;

    Entity_Item_Flag flags;
}
Entity_Item;

typedef struct Entity
{
    Entity_Kind kind;

    union
    {
        Entity_Decor decor;
        Entity_Item  item;
    };
}
Entity;

void
entity_decor_tags_show(Entity_Decor_Tags* self, paxiword level)
{
    int indent = (level + 1) * 2;

    printf("(Entity_Decor_Tags) {\n");

    for (paxiword i = 0; i < self->size; i += 1) {
        Pax_String8 item = self->items[i];

        printf("%*c", indent, PAX_ASCII_SPACE);
        printf("[%lli] = '%.*s'\n", i, pax_as(int, item.length),
            item.memory);
    }

    printf("%*c", pax_as(int, level * 2), PAX_ASCII_SPACE);
    printf("}\n");
}

void
entity_decor_show(Entity_Decor* self, paxiword level)
{
    int indent = (level + 1) * 2;

    printf("(Entity_Decor) {\n");

    printf("%*c", indent, PAX_ASCII_SPACE);
    printf(".world_x = %lli\n", self->world_x);

    printf("%*c", indent, PAX_ASCII_SPACE);
    printf(".world_y = %lli\n", self->world_y);

    printf("%*c", indent, PAX_ASCII_SPACE);
    printf(".name = '%.*s'\n", pax_as(int, self->name.length),
        self->name.memory);

    printf("%*c", indent, PAX_ASCII_SPACE);
    printf(".tags = ");

    entity_decor_tags_show(&self->tags, level + 1);

    printf("%*c", pax_as(int, level * 2), PAX_ASCII_SPACE);
    printf("}\n");
}

void
entity_item_flag_show(Entity_Item_Flag* self, paxiword level)
{
    int indent = (level + 1) * 2;

    Pax_String8 names[] = {
        pax_str8("SHOWN"),
        pax_str8("ALIVE"),
        pax_str8("SOLID"),
        pax_str8("FLUID"),
        pax_str8("FOOD"),
    };

    printf("(Entity_Item_Flag) {\n");

    for (paxiword i = 0; i < ENTITY_ITEM_FLAG_COUNT; i += 1) {
        Pax_String8 name = names[i];
        paxiword    j    = 1 << i;

        if ((*self & j) == 0) continue;

        printf("%*c", indent, PAX_ASCII_SPACE);
        printf("[%lli] = '%.*s'\n", j, pax_as(int, name.length),
            name.memory);
    }

    printf("%*c", pax_as(int, level * 2), PAX_ASCII_SPACE);
    printf("}\n");
}

void
entity_item_show(Entity_Item* self, paxiword level)
{
    int indent = (level + 1) * 2;

    printf("(Entity_Item) {\n");

    printf("%*c", indent, PAX_ASCII_SPACE);
    printf(".parent = %lli\n", self->parent);

    printf("%*c", indent, PAX_ASCII_SPACE);
    printf(".name = '%.*s'\n", pax_as(int, self->name.length),
        self->name.memory);

    printf("%*c", indent, PAX_ASCII_SPACE);
    printf(".flags = ");

    entity_item_flag_show(&self->flags, level + 1);

    printf("%*c", pax_as(int, level * 2), PAX_ASCII_SPACE);
    printf("}\n");
}

void
entity_show(Entity* self, paxiword level)
{
    switch (self->kind) {
        case ENTITY_KIND_DECOR:
            entity_decor_show(&self->decor, level);
        break;

        case ENTITY_KIND_ITEM:
            entity_item_show(&self->item, level);
        break;

        default: printf("(Entity) {}\n"); break;
    }
}

paxb8
entity_decor_tags_write(Entity_Decor_Tags* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_JSON_Message messages[16] = {};

    paxiword size = 0;

    for (paxiword i = 0; i < self->size; i += 1) {
        messages[size++] =
            pax_json_message_string(self->items[i]);
    }

    return pax_json_writer_array(writer, arena, 0, messages, size);
}

paxb8
entity_decor_write(Entity_Decor* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("world_x"), pax_json_message_unsigned(self->world_x)),
        pax_json_message_pair(pax_str8("world_y"), pax_json_message_unsigned(self->world_y)),
        pax_json_message_pair(pax_str8("name"),    pax_json_message_string(self->name)),

        pax_json_message_pair(pax_str8("tags"), pax_json_message_delegate(
            &self->tags, &entity_decor_tags_write)),
    };

    return pax_json_writer_record(writer, arena, 0, messages, 4);
}

paxb8
entity_item_flag_write(Entity_Item_Flag* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_String8 names[] = {
        pax_str8("shown"),
        pax_str8("alive"),
        pax_str8("solid"),
        pax_str8("fluid"),
        pax_str8("food"),
    };

    Pax_JSON_Message messages[16] = {};

    paxiword size = 0;

    for (paxiword i = 0; i < ENTITY_ITEM_FLAG_COUNT; i += 1) {
        paxiword j = 1 << i;

        if ((*self & j) != 0)
            messages[size++] = pax_json_message_string(names[i]);
    }

    return pax_json_writer_array(writer, arena, 0, messages, size);
}

paxb8
entity_item_write(Entity_Item* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("parent"), pax_json_message_unsigned(self->parent)),
        pax_json_message_pair(pax_str8("name"),   pax_json_message_string(self->name)),

        pax_json_message_pair(pax_str8("flags"), pax_json_message_delegate(
            &self->flags, &entity_item_flag_write)),
    };

    return pax_json_writer_record(writer, arena, 0, messages, 3);
}

paxb8
entity_write(Entity* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("decor"),
            pax_json_message_delegate(&self->decor, &entity_decor_write)),

        pax_json_message_pair(pax_str8("item"),
            pax_json_message_delegate(&self->item, &entity_item_write)),
    };

    paxiword index = 0;

    switch (self->kind) {
        case ENTITY_KIND_DECOR: index = 0; break;
        case ENTITY_KIND_ITEM:  index = 1; break;

        default: break;
    }

    return pax_json_writer_union(writer, arena, index, messages, 2);
}

int
main(int argc, char** argv)
{
    Pax_Arena   arena  = pax_memory_reserve(16);
    Pax_Buffer8 buffer = pax_buffer8_create(&arena, 256);

    Entity entity_decor = {
        .kind = ENTITY_KIND_DECOR,

        .decor = {
            .name    = pax_str8("Bush"),
            .world_x = 156,
            .world_y = 20,

            .tags = {
                .items = {
                    [0] = pax_str8("burn"),
                    [1] = pax_str8("loot"),
                },
                .size = 2,
            },
        },
    };

    Entity entity_item = {
        .kind = ENTITY_KIND_ITEM,

        .item = {
            .parent = 16,
            .name   = pax_str8("Bush"),

            .flags = ENTITY_ITEM_FLAG_ALIVE |
                ENTITY_ITEM_FLAG_SOLID |
                ENTITY_ITEM_FLAG_FOOD,
        },
    };

    Pax_JSON_Writer writer = pax_json_writer_create(&arena, 16,
        pax_target_from_buffer8(&arena, &buffer));

    entity_show(&entity_item, 0);

    entity_write(&entity_item, &writer, &arena);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        pax_as(int, buffer.length), buffer.memory);
}
