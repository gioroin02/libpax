#ifndef PAX_WINDOWS_NETWORK_SOCKET_UDP_H
#define PAX_WINDOWS_NETWORK_SOCKET_UDP_H

#include "import.h"

typedef struct Pax_Windows_Socket_UDP Pax_Windows_Socket_UDP;

Pax_Windows_Socket_UDP*
pax_windows_socket_udp_create(Pax_Arena* arena, Pax_Addr_Kind kind);

void
pax_windows_socket_udp_destroy(Pax_Windows_Socket_UDP* self);

Pax_Addr
pax_windows_socket_udp_get_addr(Pax_Windows_Socket_UDP* self);

paxu16
pax_windows_socket_udp_get_port(Pax_Windows_Socket_UDP* self);

paxb8
pax_windows_socket_udp_bind(Pax_Windows_Socket_UDP* self, Pax_Addr addr, paxu16 port);

paxb8
pax_windows_socket_udp_listen(Pax_Windows_Socket_UDP* self);

paxb8
pax_windows_socket_udp_connect(Pax_Windows_Socket_UDP* self, Pax_Addr addr, paxu16 port);

Pax_Windows_Socket_UDP*
pax_windows_socket_udp_accept(Pax_Windows_Socket_UDP* self, Pax_Arena* arena);

paxiword
pax_windows_socket_udp_write(Pax_Windows_Socket_UDP* self, paxu8* memory, paxiword length);

paxiword
pax_windows_socket_udp_write_host(Pax_Windows_Socket_UDP* self, paxu8* memory, paxiword length, Pax_Addr addr, paxu16 port);

paxiword
pax_windows_socket_udp_read(Pax_Windows_Socket_UDP* self, paxu8* memory, paxiword length);

paxiword
pax_windows_socket_udp_read_host(Pax_Windows_Socket_UDP* self, paxu8* memory, paxiword length, Pax_Addr* addr, paxu16* port);

#endif // PAX_WINDOWS_NETWORK_SOCKET_UDP_H
