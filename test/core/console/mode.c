#include "../../code/impl/console/export.h"

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    Pax_Console console = pax_console_create(&arena);
    Pax_Source* source  = pax_source_from_console(&arena, console);
    Pax_Target* target  = pax_target_from_console(&arena, console);

    pax_console_mode_apply(console, PAX_CONSOLE_MODE_RAW);

    paxb8 active = 1;

    while (active != 0) {
        paxu8 byte = pax_source_read_byte(source);

        if (byte == PAX_ASCII_LOWER_Q || byte == PAX_ASCII_UPPER_Q)
            active = 0;

        pax_target_write_byte(target, byte);
        pax_target_write_string8(target, pax_str8("\r\n"));
    }

    pax_console_destroy(console);
}
