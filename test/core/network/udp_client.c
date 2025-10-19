#include "../../code/impl/network/export.h"

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
    Pax_Socket_UDP socket;

    Pax_Buffer8 request;
    Pax_Buffer8 response;
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

    client.socket = pax_socket_udp_create(&arena, config.addr.kind);

    if (client.socket == 0) return 1;

    client.request  = pax_buffer8_create(&arena, PAX_MEMORY_KIB);
    client.response = pax_buffer8_create(&arena, PAX_MEMORY_KIB);

    Pax_Source* source = pax_source_from_buffer8(&arena, &client.response);
    Pax_Target* target = pax_target_from_buffer8(&arena, &client.request);

    pax_target_write_string8(target, CLIENT_MSG);

    pax_socket_udp_write_host(client.socket, client.request.memory,
        client.request.length, config.addr, config.port);

    pax_buffer8_clear(&client.request);

    Pax_Addr addr = {0};
    paxu16   port = 0;

    client.response.length = pax_socket_udp_read_host(client.socket,
        client.response.memory, client.response.capacity, &addr, &port);

    Pax_String8 string = pax_source_read_string8(source, &arena, PAX_MEMORY_KIB);

    if (string.length > 0) {
        if (port == config.port && pax_addr_is_equal(addr, config.addr) != 0) {
            printf(INFO " " BLU("'%.*s'") "\n",
                pax_as(int, string.length), string.memory);
        } else
            printf(ERROR " Indirizzo o porta inaspettati...\n");
    }

    pax_socket_udp_destroy(client.socket);

    pax_network_unload();
}
