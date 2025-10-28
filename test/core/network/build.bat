@echo off

set "code_core_dir=.\code\core\impl"
set "test_core_dir=.\test\core"

set "base=%code_core_dir%\base\export.c"
set "memory=%code_core_dir%\memory\export.c"
set "string=%code_core_dir%\string\export.c"
set "stream=%code_core_dir%\stream\export.c"
set "format=%code_core_dir%\format\export.c"
set "network=%code_core_dir%\network\export.c"

set "test_addr_ip4=%test_core_dir%\network\addr_ip4.c"
set "test_addr_ip6=%test_core_dir%\network\addr_ip6.c"
set "test_addr=%test_core_dir%\network\addr.c"

set "test_tcp_client=%test_core_dir%\network\tcp_client.c"
set "test_tcp_server=%test_core_dir%\network\tcp_server.c"

set "test_udp_client=%test_core_dir%\network\udp_client.c"
set "test_udp_server=%test_core_dir%\network\udp_server.c"

set "impl=%base% %memory% %string% %stream% %format% %network%"

set "lib=-lws2_32"

zig cc --std=c99 %impl% %test_addr_ip4% %lib% -o network_addr_ip4.exe
zig cc --std=c99 %impl% %test_addr_ip6% %lib% -o network_addr_ip6.exe
zig cc --std=c99 %impl% %test_addr% %lib%     -o network_addr.exe

zig cc --std=c99 %impl% %test_tcp_client% %lib% -o network_tcp_client.exe
zig cc --std=c99 %impl% %test_tcp_server% %lib% -o network_tcp_server.exe

zig cc --std=c99 %impl% %test_udp_client% %lib% -o network_udp_client.exe
zig cc --std=c99 %impl% %test_udp_server% %lib% -o network_udp_server.exe
