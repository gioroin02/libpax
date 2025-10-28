#include "../../../code/core/impl/network/export.h"

#include <stdio.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

#define FATAL MAG("FATAL")
#define ERROR RED("ERROR")
#define WARN  YLW("WARN")
#define INFO  BLU("INFO")
#define DEBUG GRN("DEBUG")
#define TRACE CYA("TRACE")

#define CLIENT_MSG pax_str8("Hello server!")

#define CLIENT_ARG_IPV4 pax_str8("--server-ipv4=")
#define CLIENT_ARG_IPV6 pax_str8("--server-ipv6=")
#define CLIENT_ARG_PORT pax_str8("--server-port=")

typedef struct ClientConfig
{
    Pax_Addr addr;
    paxuword port;
}
ClientConfig;

typedef struct Client
{
    Pax_Socket_TCP socket;
}
Client;

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    if (pax_network_load() == 0) return 1;

    ClientConfig config = {0};

    config.addr = pax_addr_localhost(PAX_ADDR_KIND_IP4);
    config.port = 8000;

    for (paxiword i = 1; i < argc; i += 1) {
        paxiword length = 32;
        paxiword stride = pax_size(paxu8);

        Pax_String8 arg = pax_string8_from_memory(argv[i], length, stride);

        if (pax_string8_begins_with(arg, CLIENT_ARG_IPV4) != 0) {
            arg = pax_string8_trim_prefix(arg, CLIENT_ARG_IPV4);
            arg = pax_string8_trim_spaces(arg);

            pax_addr_from_string8(arg, &config.addr, PAX_ADDR_KIND_IP4);
        }

        if (pax_string8_begins_with(arg, CLIENT_ARG_IPV6) != 0) {
            arg = pax_string8_trim_prefix(arg, CLIENT_ARG_IPV6);
            arg = pax_string8_trim_spaces(arg);

            pax_addr_from_string8(arg, &config.addr, PAX_ADDR_KIND_IP6);
        }

        if (pax_string8_begins_with(arg, CLIENT_ARG_PORT) != 0) {
            arg = pax_string8_trim_prefix(arg, CLIENT_ARG_PORT);
            arg = pax_string8_trim_spaces(arg);

            pax_unsigned_from_string8(arg, &config.port, PAX_FORMAT_RADIX_10, 0);
        }
    }

    Client client = {0};

    client.socket = pax_socket_tcp_create(&arena, config.addr.kind);

    if (client.socket == 0) return 1;

    if (pax_socket_tcp_connect(client.socket, config.addr, config.port) == 0)
        return 1;

    Pax_Source* source = pax_source_from_socket_tcp(&arena, client.socket);
    Pax_Target* target = pax_target_from_socket_tcp(&arena, client.socket);

    pax_target_write_string8(target, CLIENT_MSG);

    Pax_String8 string = pax_source_read_string8(source, &arena, PAX_MEMORY_KIB);

    if (string.length > 0) {
        printf(INFO " " BLU("'%.*s'") "\n",
            pax_as(int, string.length), string.memory);
    }

    pax_socket_tcp_destroy(client.socket);

    pax_network_unload();
}
