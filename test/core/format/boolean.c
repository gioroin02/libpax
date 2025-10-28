#include "../../../code/core/impl/format/export.h"

#include <stdio.h>

void
test_case(Pax_Arena* arena, paxbword value)
{
    Pax_Format_Flag flags = PAX_FORMAT_FLAG_UPPER;

    paxuword result = 0;

    Pax_String8 string = pax_string8_from_boolean(arena, value, flags);

    paxb8 state  = pax_boolean_from_string8(string, &result, flags);

    printf("%llu -> '%.*s' [%lli] -> %llu [%s]\n", value,
        pax_as(int, string.length), string.memory, string.length,
        result, state != 0 ? "ok" : "ko");
}

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    test_case(&arena, 1);
    test_case(&arena, 0);
}
