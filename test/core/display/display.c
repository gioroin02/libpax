#include "../../../code/core/impl/display/export.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(32);
    Pax_Arena video = pax_memory_reserve(512);

    Pax_Display display = pax_display_create(&arena, pax_str8("Prova"),
        pax_display_message_queue_create(&arena, 32));

    if (display == 0) return 1;

    printf("DISPLAY CREATED\n");

    Pax_Display_Buffer buffer_array[2] = {
        pax_display_buffer_create(display, &video, 400, 400),
        pax_display_buffer_create(display, &video, 400, 400),
    };

    if (buffer_array[0] == 0) return 1;

    printf("DISPLAY BUFFER[0] CREATED\n");

    if (buffer_array[1] == 0) return 1;

    printf("DISPLAY BUFFER[1] CREATED\n");

    paxiword buffer_index = 0;
    paxb8    active       = 1;

    srand(time(0));

    pax_display_set_visibility(display, PAX_DISPLAY_VISIBILITY_SHOW);

    while (active != 0) {
        Pax_Display_Message message = {0};

        while (pax_display_poll_message(display, &message) != 0) {
            switch (message.kind) {
                case PAX_DISPLAY_MESSAGE_KIND_DISPLAY_DESTROY:
                    active = 0;
                break;

                case PAX_DISPLAY_MESSAGE_KIND_KEYBOARD_BUTTON: {
                    Pax_Display_Message_Keyboard_Button button = message.keyboard_button;

                    if (button.button == PAX_KEYBOARD_BUTTON_ESCAPE)
                        active = button.active;
                } break;

                case PAX_DISPLAY_MESSAGE_KIND_MOUSE_BUTTON: {
                    Pax_Display_Message_Mouse_Button button = message.mouse_button;

                    switch (button.button) {
                        case PAX_MOUSE_BUTTON_LEFT:
                            printf("Mouse_Button {l = %u}\n", button.active);
                        break;

                        case PAX_MOUSE_BUTTON_MIDDLE:
                            printf("Mouse_Button {m = %u}\n", button.active);
                        break;

                        case PAX_MOUSE_BUTTON_RIGHT:
                            printf("Mouse_Button {r = %u}\n", button.active);
                        break;

                        default: break;
                    }
                } break;

                case PAX_DISPLAY_MESSAGE_KIND_DISPLAY_SIZE: {
                    Pax_Display_Message_Display_Size size = message.display_size;

                    printf("Display_Size {x = %lli, y = %lli}\n", size.width, size.height);

                    pax_display_clear(display);
                } break;

                case PAX_DISPLAY_MESSAGE_KIND_DISPLAY_COORDS: {
                    Pax_Display_Message_Display_Coords size = message.display_coords;

                    printf("Display_Coords {x = %lli, y = %lli}\n", size.x, size.y);
                } break;

                default: break;
            }
        }

        Pax_Display_Buffer buffer = buffer_array[buffer_index];

        paxiword width  = pax_display_buffer_width(buffer);
        paxiword height = pax_display_buffer_height(buffer);

        for (paxiword y = 0; y < height; y += 1) {
            for (paxiword x = 0; x < width; x += 1) {
                paxu8 r = 96 + rand() % 64;
                paxu8 g = 96 + rand() % 64;
                paxu8 b = 96 + rand() % 64;

                pax_display_buffer_write(
                    buffer, x, y, r, g, b);
            }
        }

        pax_display_flush(display, buffer);

        buffer_index = (buffer_index + 1) % 2;
    }

    for (paxiword i = 0; i < 2; i += 1)
        pax_display_buffer_destroy(buffer_array[i]);

    pax_display_destroy(display);
}
