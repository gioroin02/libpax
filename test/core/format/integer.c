#include "../../code/impl/format/export.h"

#include <stdio.h>

void
test_case(Pax_Arena* arena, paxiword value)
{
    Pax_Format_Radix radix = PAX_FORMAT_RADIX_16;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_UPPER | PAX_FORMAT_FLAG_PLUS;

    paxiword result = 0;

    Pax_String8 string = pax_string8_from_integer(arena, value, radix, flags);

    paxb8 state  = pax_integer_from_string8(string, &result, radix, flags);

    printf("%lli -> '%.*s' [%lli] -> %lli [%s]\n", value,
        pax_as(int, string.length), string.memory, string.length,
        result, state != 0 ? "ok" : "ko");
}

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    test_case(&arena, +248);
    test_case(&arena, -248);
}
