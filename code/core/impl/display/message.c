#ifndef PAX_CORE_DISPLAY_MESSAGE_C
#define PAX_CORE_DISPLAY_MESSAGE_C

#include "./message.h"

Pax_Display_Message
pax_display_message_display_destroy()
{
    return (Pax_Display_Message) {
        .kind = PAX_DISPLAY_MESSAGE_KIND_DISPLAY_DESTROY,
    };
}

Pax_Display_Message
pax_display_message_keyboard_button(Pax_Keyboard_Button button, paxb8 down, paxiword scan)
{
    return (Pax_Display_Message) {
        .kind = PAX_DISPLAY_MESSAGE_KIND_KEYBOARD_BUTTON,

        .keyboard_button = {
            .button = button,
            .scan   = scan,
            .down   = down,
        },
    };
}

Pax_Display_Message
pax_display_message_mouse_button(Pax_Mouse_Button button, paxb8 down)
{
    return (Pax_Display_Message) {
        .kind = PAX_DISPLAY_MESSAGE_KIND_MOUSE_BUTTON,

        .mouse_button = {
            .button = button,
            .down   = down,
        },
    };
}

#endif // PAX_CORE_DISPLAY_MESSAGE_C
