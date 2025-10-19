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

#define SERVER_MSG pax_str8("Hello client!")

#define SERVER_ARG_IP4      pax_str8("--server-ipv4")
#define SERVER_ARG_IP6      pax_str8("--server-ipv6")
#define SERVER_ARG_PORT     pax_str8("--server-port=")
#define SERVER_ARG_LIFETIME pax_str8("--server-lifetime=")

typedef struct ServerConfig
{
    Pax_Addr addr;
    paxuword port;
    paxuword lifetime;
}
ServerConfig;

typedef struct Server
{
    Pax_Socket_TCP socket;
}
Server;

typedef struct ServerSession
{
    Pax_Socket_TCP socket;
}
ServerSession;

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(16);

    if (pax_network_load() == 0) return 1;

    ServerConfig config = {0};

    config.addr     = pax_addr_any(PAX_ADDR_KIND_IP4);
    config.port     = 8000,
    config.lifetime = 1;

    for (paxiword i = 1; i < argc; i += 1) {
        paxiword length = 32;
        paxiword stride = pax_size(paxu8);

        Pax_String8 arg = pax_string8_from_memory(argv[i], length, stride);

        if (pax_string8_is_equal(arg, SERVER_ARG_IP4) != 0)
            config.addr = pax_addr_any(PAX_ADDR_KIND_IP4);

        if (pax_string8_is_equal(arg, SERVER_ARG_IP6) != 0)
            config.addr = pax_addr_any(PAX_ADDR_KIND_IP6);

        if (pax_string8_begins_with(arg, SERVER_ARG_PORT) != 0) {
            arg = pax_string8_trim_prefix(arg, SERVER_ARG_PORT);
            arg = pax_string8_trim_spaces(arg);

            pax_unsigned_from_string8(arg, &config.port, PAX_FORMAT_RADIX_10, 0);
        }

        if (pax_string8_begins_with(arg, SERVER_ARG_LIFETIME) != 0) {
            arg = pax_string8_trim_prefix(arg, SERVER_ARG_LIFETIME);
            arg = pax_string8_trim_spaces(arg);

            pax_unsigned_from_string8(arg, &config.lifetime, PAX_FORMAT_RADIX_10, 0);
        }
    }

    Server server = {0};

    server.socket = pax_socket_tcp_create(&arena, config.addr.kind);

    if (server.socket == 0) return 1;

    if (pax_socket_tcp_bind(server.socket, config.addr, config.port) == 0)
        return 1;

    if (pax_socket_tcp_listen(server.socket) == 0) return 1;

    paxiword mark = pax_arena_tell(&arena);

    for (paxu32 i = 0; i < config.lifetime; i += 1) {
        ServerSession session = {0};

        session.socket = pax_socket_tcp_accept(server.socket, &arena);

        if (session.socket == 0) continue;

        Pax_Source* source = pax_source_from_socket_tcp(&arena, session.socket);
        Pax_Target* target = pax_target_from_socket_tcp(&arena, session.socket);

        Pax_String8 string = pax_source_read_string8(source, &arena, PAX_MEMORY_KIB);

        if (string.length > 0) {
            printf(INFO " " BLU("'%.*s'") "\n",
                pax_as(int, string.length), string.memory);

            pax_target_write_string8(target, SERVER_MSG);
        }

        pax_socket_tcp_destroy(session.socket);

        pax_arena_rewind(&arena, mark, 0);
    }

    pax_socket_tcp_destroy(server.socket);

    pax_network_unload();
}
