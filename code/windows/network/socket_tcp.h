#ifndef PAX_WINDOWS_NETWORK_SOCKET_TCP_H
#define PAX_WINDOWS_NETWORK_SOCKET_TCP_H

#include "./import.h"

typedef struct Pax_Windows_Socket_TCP Pax_Windows_Socket_TCP;

Pax_Windows_Socket_TCP*
pax_windows_socket_tcp_create(Pax_Arena* arena, Pax_Addr_Kind kind);

void
pax_windows_socket_tcp_destroy(Pax_Windows_Socket_TCP* self);

Pax_Addr
pax_windows_socket_tcp_get_addr(Pax_Windows_Socket_TCP* self);

paxu16
pax_windows_socket_tcp_get_port(Pax_Windows_Socket_TCP* self);

paxb8
pax_windows_socket_tcp_bind(Pax_Windows_Socket_TCP* self, Pax_Addr addr, paxu16 port);

paxb8
pax_windows_socket_tcp_listen(Pax_Windows_Socket_TCP* self);

paxb8
pax_windows_socket_tcp_connect(Pax_Windows_Socket_TCP* self, Pax_Addr addr, paxu16 port);

Pax_Windows_Socket_TCP*
pax_windows_socket_tcp_accept(Pax_Windows_Socket_TCP* self, Pax_Arena* arena);

paxiword
pax_windows_socket_tcp_write(Pax_Windows_Socket_TCP* self, paxu8* memory, paxiword length);

paxiword
pax_windows_socket_tcp_read(Pax_Windows_Socket_TCP* self, paxu8* memory, paxiword length);

#endif // PAX_WINDOWS_NETWORK_SOCKET_TCP_H
