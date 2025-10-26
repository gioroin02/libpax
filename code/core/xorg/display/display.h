#ifndef PAX_XORG_DISPLAY_DISPLAY_H
#define PAX_XORG_DISPLAY_DISPLAY_H

#include "./import.h"

typedef struct Pax_Xorg_Display        Pax_Xorg_Display;
typedef struct Pax_Xorg_Display_Buffer Pax_Xorg_Display_Buffer;

/* Display */

Pax_Xorg_Display*
pax_xorg_display_create(Pax_Arena* arena, Pax_String8 name);

void
pax_xorg_display_destroy(Pax_Xorg_Display* self);

void
pax_xorg_display_flush(Pax_Xorg_Display* self, Pax_Xorg_Display_Buffer* buffer);

paxb8
pax_xorg_display_set_visibility(Pax_Xorg_Display* self, Pax_Display_Visibility visibility);

paxb8
pax_xorg_display_poll_message(Pax_Xorg_Display* self, Pax_Display_Message* value);

/* Display Buffer */

Pax_Xorg_Display_Buffer*
pax_xorg_display_buffer_create(Pax_Xorg_Display* self, Pax_Arena* arena, paxiword x, paxiword y);

void
pax_xorg_display_buffer_destroy(Pax_Xorg_Display_Buffer* self);

paxiword
pax_xorg_display_buffer_length(Pax_Xorg_Display_Buffer* self);

paxiword
pax_xorg_display_buffer_width(Pax_Xorg_Display_Buffer* self);

paxiword
pax_xorg_display_buffer_height(Pax_Xorg_Display_Buffer* self);

paxiword
pax_xorg_display_buffer_stride(Pax_Xorg_Display_Buffer* self);

paxb8
pax_xorg_display_buffer_write(Pax_Xorg_Display_Buffer* self, paxiword x, paxiword y, paxu8 r, paxu8 g, paxu8 b, paxu8 a);

paxb8
pax_xorg_display_buffer_read(Pax_Xorg_Display_Buffer* self, paxiword x, paxiword y, paxu8* r, paxu8* g, paxu8* b, paxu8* a);

#endif // PAX_XORG_DISPLAY_DISPLAY_H
