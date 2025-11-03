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
entity_decor_tags_read(Entity_Decor_Tags* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[16] = {
        pax_json_message_string(pax_str8("")),
    };

    paxiword size = 0;

    if (pax_json_reader_array(reader, arena, &size, messages, 16) == 0)
        return 0;

    for (paxiword i = 0; i < size; i += 1) {
        Pax_String8 name = messages[i].value_string;

        if (name.length > 0)
            self->items[self->size++] = name;
    }

    return 1;
}

paxb8
entity_decor_read(Entity_Decor* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("world_x"), pax_json_message_unsigned(0)),
        pax_json_message_pair(pax_str8("world_y"), pax_json_message_unsigned(0)),
        pax_json_message_pair(pax_str8("name"),    pax_json_message_string(pax_str8(""))),

        pax_json_message_pair(pax_str8("tags"), pax_json_message_delegate(
            &self->tags, &entity_decor_tags_read)),
    };

    if (pax_json_reader_record(reader, arena, 0, messages, 4) == 0)
        return 0;

    self->world_x = messages[0].value_unsigned;
    self->world_y = messages[1].value_unsigned;
    self->name    = messages[2].value_string;

    return 1;
}

paxb8
entity_item_flag_read(Entity_Item_Flag* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[16] = {
        pax_json_message_string(pax_str8("")),
    };

    paxiword size = 0;

    if (pax_json_reader_array(reader, arena, &size, messages, 16) == 0)
        return 0;

    for (paxiword i = 0; i < size; i += 1) {
        Pax_String8 name = messages[i].value_string;

        if (pax_string8_is_equal(name, pax_str8("shown")) != 0)
            *self |= ENTITY_ITEM_FLAG_SHOWN;

        if (pax_string8_is_equal(name, pax_str8("alive")) != 0)
            *self |= ENTITY_ITEM_FLAG_ALIVE;

        if (pax_string8_is_equal(name, pax_str8("solid")) != 0)
            *self |= ENTITY_ITEM_FLAG_SOLID;

        if (pax_string8_is_equal(name, pax_str8("fluid")) != 0)
            *self |= ENTITY_ITEM_FLAG_FLUID;

        if (pax_string8_is_equal(name, pax_str8("food")) != 0)
            *self |= ENTITY_ITEM_FLAG_FOOD;
    }

    return 1;
}

paxb8
entity_item_read(Entity_Item* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("parent"), pax_json_message_unsigned(0)),
        pax_json_message_pair(pax_str8("name"),   pax_json_message_string(pax_str8(""))),

        pax_json_message_pair(pax_str8("flags"), pax_json_message_delegate(
            &self->flags, &entity_item_flag_read)),
    };

    if (pax_json_reader_record(reader, arena, 0, messages, 3) == 0)
        return 0;

    self->parent = messages[0].value_unsigned;
    self->name   = messages[1].value_string;

    return 1;
}

paxb8
entity_read(Entity* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("decor"),
            pax_json_message_delegate(&self->decor, &entity_decor_read)),

        pax_json_message_pair(pax_str8("item"),
            pax_json_message_delegate(&self->item, &entity_item_read)),
    };

    paxiword index = 0;

    if (pax_json_reader_union(reader, arena, &index, messages, 2) == 0)
        return 0;

    switch (index) {
        case 0: self->kind = ENTITY_KIND_DECOR; break;
        case 1: self->kind = ENTITY_KIND_ITEM;  break;

        default: break;
    }

    return self->kind != ENTITY_KIND_NONE ? 1 : 0;
}

#define ENTITY_DECOR pax_str8( \
    "{\"decor\":{\"name\":\"Bush\",\"world_x\":156,\"world_y\":20,\"tags\":[\"burn\",\"loot\"]}}" \
)

#define ENTITY_ITEM pax_str8( \
    "{\"item\":{\"parent\":16,\"name\":\"Bush\",\"flags\":[\"alive\",\"solid\",\"food\"]}}" \
)

int
main(int argc, char** argv)
{
    Pax_Arena   arena  = pax_memory_reserve(16);
    Pax_Buffer8 buffer = pax_buffer8_create(&arena, 256);

    Entity entity = {0};

    pax_buffer8_write_tail_string8(&buffer, ENTITY_DECOR);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        pax_as(int, buffer.length), buffer.memory);

    printf("\n");

    Pax_Scanner scanner = pax_scanner_create(&arena, 1,
        pax_source_from_buffer8(&arena, &buffer));

    Pax_JSON_Reader reader = pax_json_reader_create(&arena, 16, scanner);

    entity_read(&entity, &reader, &arena);

    entity_show(&entity, 1);
}
