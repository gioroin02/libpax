@echo off

set "impl_dir=.\code\impl"
set "test_dir=.\test"

set "impl_base=%impl_dir%\base\export.c"
set "impl_memory=%impl_dir%\memory\export.c"
set "impl_string=%impl_dir%\string\export.c"
set "impl_stream=%impl_dir%\stream\export.c"
set "impl_format=%impl_dir%\format\export.c"
set "impl_network=%impl_dir%\network\export.c"

set "test_addr_ip4=%test_dir%\network\addr_ip4.c"
set "test_addr_ip6=%test_dir%\network\addr_ip6.c"
set "test_addr=%test_dir%\network\addr.c"

set "test_tcp_client=%test_dir%\network\tcp_client.c"
set "test_tcp_server=%test_dir%\network\tcp_server.c"

set "test_udp_client=%test_dir%\network\udp_client.c"
set "test_udp_server=%test_dir%\network\udp_server.c"

set "impl=%impl_base% %impl_memory% %impl_string% %impl_stream% %impl_format% %impl_network%"

set "lib=-lws2_32"

zig cc --std=c99 %impl% %test_addr_ip4% %lib% -o network_addr_ip4.exe
zig cc --std=c99 %impl% %test_addr_ip6% %lib% -o network_addr_ip6.exe
zig cc --std=c99 %impl% %test_addr% %lib%     -o network_addr.exe

zig cc --std=c99 %impl% %test_tcp_client% %lib% -o network_tcp_client.exe
zig cc --std=c99 %impl% %test_tcp_server% %lib% -o network_tcp_server.exe

zig cc --std=c99 %impl% %test_udp_client% %lib% -o network_udp_client.exe
zig cc --std=c99 %impl% %test_udp_server% %lib% -o network_udp_server.exe
