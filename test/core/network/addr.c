#include "../../../code/core/impl/network/export.h"

#include <stdio.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

#define TRUE  GRN("T")
#define FALSE RED("F")

void
showAddr_from_string8(Pax_String8 string, Pax_Addr_Kind kind)
{
    Pax_Addr value = {0};
    paxb8    state = pax_addr_from_string8(string, &value, kind);

    switch (kind) {
        case PAX_ADDR_KIND_IP4: {
            printf("ip4 (" BLU("'%24s'") ") -> %s, ",
                string.memory, state ? TRUE : FALSE);

            for (paxiword i = 0; i < PAX_ADDR_IP4_GROUPS; i += 1)
                printf("%4u ", value.ip4.items[i]);
            printf("\n");
        } break;

        case PAX_ADDR_KIND_IP6: {
            printf("ip6 (" BLU("'%48s'") ") -> %s, ",
                string.memory, state ? TRUE : FALSE);

            for (paxiword i = 0; i < PAX_ADDR_IP6_GROUPS; i += 1)
                printf("%4x ", value.ip6.items[i]);
            printf("\n");
        } break;

        default: break;
    }
}

int
main()
{
    printf("Valid IPv4:\n");

    showAddr_from_string8(pax_str8("0.0.0.0"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("000.0.000.0"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("127.0.0.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("10.0.0.255"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("172.16.0.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("255.255.255.255"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("8.8.8.8"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("100.64.0.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("169.254.1.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("198.51.100.42"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("1.2.3.4"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("203.0.113.7"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("128.0.0.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.0.2.123"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("172.31.255.254"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("10.10.10.10"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.0.0"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.001.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1.01"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("172.20.30.40"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("209.85.231.104"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("240.0.0.1"), PAX_ADDR_KIND_IP4);

    printf("\nInvalid IPv4:\n");

    showAddr_from_string8(pax_str8("localhost"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("256.1.2.3"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("1.2.3"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("1.2.3.4.5"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("10.0.0.0.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("172.16.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1.1.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("1.2.3.4."), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8(".1.2.3.4"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1.256"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("abc.def.ghi.jkl"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1."), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1.1/24"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1.1..2"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.-1.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1.1a"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1.999"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1.1.2"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1."), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168..1.1"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1.1:80"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("300.400.500.600"), PAX_ADDR_KIND_IP4);
    showAddr_from_string8(pax_str8("192.168.1.1/32"), PAX_ADDR_KIND_IP4);

    printf("\nValid IPv6:\n");

    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("fc00::1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("::1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("::"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:db8::8a2e:370:7334"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("fe80::1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("ff02::1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:0000:0000:0000:0000:0000:0001"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:db8:0:0:0:0:0:1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:db8::1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("3ffe:1900:4545:3:200:f8ff:fe21:67cf"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:db8:1234::5678"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("ff00::"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3::8a2e:0370:7334"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:db8:0:0:1:0:0:1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("fe80::200:5eff:fe00:5213"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:db8:abcd:1234:5678:90ab:cdef:1234"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("::ffff:0:0"), PAX_ADDR_KIND_IP6);

    printf("\nInvalid IPv6:\n");

    showAddr_from_string8(pax_str8("localhost"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("fe80:0:0:0:200:5efe:192.168.1.1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("::ffff:192.168.1.1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8::85a3::7334"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("gggg:hhhh:iiii:jjjj:kkkk:llll:mmmm:nnnn"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:733g"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8(":2001:0db8:85a3:0000:0000:8a2e:0370:7334"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::7334:1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370.7334"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334/64"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::7334:abcd"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:::7334"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334::"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:FFFFF"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001::85a3::"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:port"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("::ffff:192.168.1.256"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::-1"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:5"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:733.4"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e::7334::"), PAX_ADDR_KIND_IP6);
    showAddr_from_string8(pax_str8("2001:0db8:85a3:0000:0000:8a2e:0370:"), PAX_ADDR_KIND_IP6);
}
