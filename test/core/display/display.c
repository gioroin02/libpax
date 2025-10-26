#include "../../../code/core/impl/display/export.h"
#include "../../../code/core/impl/process/export.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

int
main(int argc, char** argv)
{
    Pax_Arena   arena   = pax_memory_reserve(16);
    Pax_Display display = pax_display_create(&arena, pax_str8("Prova"));

    if (display == 0) return 1;

    Pax_Display_Buffer buffer_array[2] = {
        pax_display_buffer_create(display, &arena, 400, 300),
        pax_display_buffer_create(display, &arena, 400, 300),
    };

    paxiword buffer_index = 0;
    paxb8    active       = 1;

    srand(time(0));

    pax_display_set_visibility(display,
        PAX_DISPLAY_VISIBILITY_SHOW);

    while (active != 0) {
        Pax_Display_Message message = {0};

        while (pax_display_poll_message(display, &message) != 0) {
            switch (message.kind) {
                case PAX_DISPLAY_MESSAGE_KIND_CLOSE:
                    active = 0;
                break;

                case PAX_DISPLAY_MESSAGE_KIND_KEYBD_BUTTON: {
                    Pax_Display_Message_Keybd_Button button = message.keybd_button;

                    if (button.button == PAX_KEYBD_BUTTON_ESCAPE)
                        active = button.down;
                } break;

                case PAX_DISPLAY_MESSAGE_KIND_MOUSE_BUTTON: {
                    Pax_Display_Message_Mouse_Button button = message.mouse_button;

                    if (button.button == PAX_MOUSE_BUTTON_LEFT)
                        printf("left = %u\n", button.down);
                } break;


                default: break;
            }
        }

        // disegna su bitmap

        // copia bitmap su buffer

        Pax_Display_Buffer buffer = buffer_array[buffer_index];

        paxiword width  = pax_display_buffer_width(buffer);
        paxiword height = pax_display_buffer_height(buffer);

        for (paxiword y = 0; y < height; y += 1) {
            for (paxiword x = 0; x < width; x += 1) {
                paxu8 r = 96 + rand() % 64;
                paxu8 g = 96 + rand() % 64;
                paxu8 b = 96 + rand() % 64;

                pax_display_buffer_write(buffer, x, y,
                    r, g, b, 255);
            }
        }

        pax_display_flush(display, buffer);

        buffer_index = (buffer_index + 1) % 2;
    }

    for (paxiword i = 0; i < 2; i += 1)
        pax_display_buffer_destroy(buffer_array[i]);

    pax_display_destroy(display);
}
