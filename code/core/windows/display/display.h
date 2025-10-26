#ifndef PAX_WINDOWS_DISPLAY_DISPLAY_H
#define PAX_WINDOWS_DISPLAY_DISPLAY_H

#include "./import.h"

typedef struct Pax_Windows_Display        Pax_Windows_Display;
typedef struct Pax_Windows_Display_Buffer Pax_Windows_Display_Buffer;

/* Display */

Pax_Windows_Display*
pax_windows_display_create(Pax_Arena* arena, Pax_String8 name);

void
pax_windows_display_destroy(Pax_Windows_Display* self);

void
pax_windows_display_flush(Pax_Windows_Display* self, Pax_Windows_Display_Buffer* buffer);

paxb8
pax_windows_display_set_visibility(Pax_Windows_Display* self, Pax_Display_Visibility visibility);

paxb8
pax_windows_display_poll_message(Pax_Windows_Display* self, Pax_Display_Message* value);

/* Display Buffer */

Pax_Windows_Display_Buffer*
pax_windows_display_buffer_create(Pax_Windows_Display* self, Pax_Arena* arena, paxiword width, paxiword height);

void
pax_windows_display_buffer_destroy(Pax_Windows_Display_Buffer* self);

paxiword
pax_windows_display_buffer_length(Pax_Windows_Display_Buffer* self);

paxiword
pax_windows_display_buffer_width(Pax_Windows_Display_Buffer* self);

paxiword
pax_windows_display_buffer_height(Pax_Windows_Display_Buffer* self);

paxiword
pax_windows_display_buffer_stride(Pax_Windows_Display_Buffer* self);

paxb8
pax_windows_display_buffer_write(Pax_Windows_Display_Buffer* self, paxiword x, paxiword y, paxu8 r, paxu8 g, paxu8 b, paxu8 a);

paxb8
pax_windows_display_buffer_read(Pax_Windows_Display_Buffer* self, paxiword x, paxiword y, paxu8* r, paxu8* g, paxu8* b, paxu8* a);

#endif // PAX_WINDOWS_DISPLAY_DISPLAY_H
