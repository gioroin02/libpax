#ifndef PAX_CORE_DISPLAY_MESSAGE_C
#define PAX_CORE_DISPLAY_MESSAGE_C

#include "./message.h"

Pax_Display_Message
pax_display_message_close()
{
    return (Pax_Display_Message) {
        .kind = PAX_DISPLAY_MESSAGE_KIND_CLOSE,
    };
}

Pax_Display_Message
pax_display_message_keybd_button(Pax_Keybd_Button button, paxb8 down, paxiword scan)
{
    return (Pax_Display_Message) {
        .kind = PAX_DISPLAY_MESSAGE_KIND_KEYBD_BUTTON,

        .keybd_button = {
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
