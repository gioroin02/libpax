#ifndef PAX_ENCODING_JSON_WRITER_H
#define PAX_ENCODING_JSON_WRITER_H

#include "./message.h"

typedef enum Pax_JSON_Writer_Flag
{
    PAX_JSON_WRITER_NONE  = 0,
    PAX_JSON_WRITER_COMMA = 1 << 0,
}
Pax_JSON_Writer_Flag;

typedef struct Pax_JSON_Writer
{
    Pax_Array_Ring stack;
    Pax_Target*    target;

    Pax_JSON_Writer_Flag flags;
}
Pax_JSON_Writer;

typedef paxb8 (Pax_JSON_Writer_Proc) (void*, Pax_JSON_Writer*, Pax_Arena*);

Pax_JSON_Writer
pax_json_writer_create(Pax_Arena* arena, paxiword length, Pax_Target* target);

paxb8
pax_json_writer_message(Pax_JSON_Writer* self, Pax_Arena* arena, Pax_JSON_Message message);

paxiword
pax_json_writer_many(Pax_JSON_Writer* self, Pax_Arena* arena, Pax_JSON_Message* values, paxiword length);

paxb8
pax_json_writer_object_open(Pax_JSON_Writer* self, Pax_Arena* arena);

paxb8
pax_json_writer_object_close(Pax_JSON_Writer* self, Pax_Arena* arena);

paxb8
pax_json_writer_array_open(Pax_JSON_Writer* self, Pax_Arena* arena);

paxb8
pax_json_writer_array_close(Pax_JSON_Writer* self, Pax_Arena* arena);

#endif // PAX_ENCODING_JSON_WRITER_H
