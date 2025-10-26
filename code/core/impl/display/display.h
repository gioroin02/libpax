#ifndef PAX_CORE_DISPLAY_DISPLAY_H
#define PAX_CORE_DISPLAY_DISPLAY_H

#include "./config.h"
#include "./message.h"

typedef void* Pax_Display;
typedef void* Pax_Display_Buffer;

/* Display */

Pax_Display
pax_display_create(Pax_Arena* arena, Pax_String8 name);

void
pax_display_destroy(Pax_Display self);

void
pax_display_flush(Pax_Display self, Pax_Display_Buffer buffer);

paxb8
pax_display_set_visibility(Pax_Display self, Pax_Display_Visibility visibility);

paxb8
pax_display_poll_message(Pax_Display self, Pax_Display_Message* value);

/* Display Buffer */

Pax_Display_Buffer
pax_display_buffer_create(Pax_Display self, Pax_Arena* arena, paxiword width, paxiword height);

void
pax_display_buffer_destroy(Pax_Display_Buffer self);

paxiword
pax_display_buffer_length(Pax_Display_Buffer self);

paxiword
pax_display_buffer_width(Pax_Display_Buffer self);

paxiword
pax_display_buffer_height(Pax_Display_Buffer self);

paxiword
pax_display_buffer_stride(Pax_Display_Buffer self);

paxb8
pax_display_buffer_write(Pax_Display_Buffer self, paxiword x, paxiword y, paxu8 r, paxu8 g, paxu8 b, paxu8 a);

paxb8
pax_display_buffer_read(Pax_Display_Buffer self, paxiword x, paxiword y, paxu8* r, paxu8* g, paxu8* b, paxu8* a);

#endif // PAX_CORE_DISPLAY_DISPLAY_H
