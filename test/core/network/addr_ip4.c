#include "../../code/impl/network/export.h"

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
showAddrIp4_from_string8(Pax_String8 string)
{
    Pax_Addr_IP4 value = {};
    paxb8      state = pax_addr_ip4_from_string8(string, &value);

    printf("ip6 (" BLU("'%24s'") ") -> %s, ",
        string.memory, state != 0 ? TRUE : FALSE);

    for (paxiword i = 0; i < PAX_ADDR_IP4_GROUPS; i += 1)
        printf("%4u ", value.items[i]);
    printf("\n");
}

int
main()
{
    printf("Valid IPv4:\n");

    showAddrIp4_from_string8(pax_str8("0.0.0.0"));
    showAddrIp4_from_string8(pax_str8("000.0.000.0"));
    showAddrIp4_from_string8(pax_str8("127.0.0.1"));
    showAddrIp4_from_string8(pax_str8("192.168.1.1"));
    showAddrIp4_from_string8(pax_str8("10.0.0.255"));
    showAddrIp4_from_string8(pax_str8("172.16.0.1"));
    showAddrIp4_from_string8(pax_str8("255.255.255.255"));
    showAddrIp4_from_string8(pax_str8("8.8.8.8"));
    showAddrIp4_from_string8(pax_str8("100.64.0.1"));
    showAddrIp4_from_string8(pax_str8("169.254.1.1"));
    showAddrIp4_from_string8(pax_str8("198.51.100.42"));
    showAddrIp4_from_string8(pax_str8("1.2.3.4"));
    showAddrIp4_from_string8(pax_str8("203.0.113.7"));
    showAddrIp4_from_string8(pax_str8("128.0.0.1"));
    showAddrIp4_from_string8(pax_str8("192.0.2.123"));
    showAddrIp4_from_string8(pax_str8("172.31.255.254"));
    showAddrIp4_from_string8(pax_str8("10.10.10.10"));
    showAddrIp4_from_string8(pax_str8("192.168.0.0"));
    showAddrIp4_from_string8(pax_str8("192.168.001.1"));
    showAddrIp4_from_string8(pax_str8("192.168.1.01"));
    showAddrIp4_from_string8(pax_str8("172.20.30.40"));
    showAddrIp4_from_string8(pax_str8("209.85.231.104"));
    showAddrIp4_from_string8(pax_str8("240.0.0.1"));

    printf("\nInvalid IPv4:\n");

    showAddrIp4_from_string8(pax_str8("localhost"));
    showAddrIp4_from_string8(pax_str8("256.1.2.3"));
    showAddrIp4_from_string8(pax_str8("1.2.3"));
    showAddrIp4_from_string8(pax_str8("1.2.3.4.5"));
    showAddrIp4_from_string8(pax_str8("10.0.0.0.1"));
    showAddrIp4_from_string8(pax_str8("172.16.1"));
    showAddrIp4_from_string8(pax_str8("192.168.1.1.1"));
    showAddrIp4_from_string8(pax_str8("1.2.3.4."));
    showAddrIp4_from_string8(pax_str8(".1.2.3.4"));
    showAddrIp4_from_string8(pax_str8("192.168.1.256"));
    showAddrIp4_from_string8(pax_str8("abc.def.ghi.jkl"));
    showAddrIp4_from_string8(pax_str8("192.168.1."));
    showAddrIp4_from_string8(pax_str8("192.168.1.1/24"));
    showAddrIp4_from_string8(pax_str8("192.168.1.1..2"));
    showAddrIp4_from_string8(pax_str8("192.168.-1.1"));
    showAddrIp4_from_string8(pax_str8("192.168.1.1a"));
    showAddrIp4_from_string8(pax_str8("192.168.1"));
    showAddrIp4_from_string8(pax_str8("192.168.1.999"));
    showAddrIp4_from_string8(pax_str8("192.168.1.1.2"));
    showAddrIp4_from_string8(pax_str8("192.168.1."));
    showAddrIp4_from_string8(pax_str8("192.168..1.1"));
    showAddrIp4_from_string8(pax_str8("192.168.1.1:80"));
    showAddrIp4_from_string8(pax_str8("300.400.500.600"));
    showAddrIp4_from_string8(pax_str8("192.168.1.1/32"));
}
