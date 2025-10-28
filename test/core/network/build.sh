code_core_dir="./code/core/impl"
test_core_dir="./test/core"

base="$code_core_dir/base/export.c"
memory="$code_core_dir/memory/export.c"
string="$code_core_dir/string/export.c"
stream="$code_core_dir/stream/export.c"
format="$code_core_dir/format/export.c"
network="$code_core_dir/network/export.c"

test_addr_ip4="$test_core_dir/network/addr_ip4.c"
test_addr_ip6="$test_core_dir/network/addr_ip6.c"
test_addr="$test_core_dir/network/addr.c"

test_tcp_client="$test_core_dir/network/tcp_client.c"
test_tcp_server="$test_core_dir/network/tcp_server.c"

test_udp_client="$test_core_dir/network/udp_client.c"
test_udp_server="$test_core_dir/network/udp_server.c"

impl="$base $memory $string $stream $format $network"

gcc --std=c99 $impl $test_addr_ip4 -o network_addr_ip4.exe
gcc --std=c99 $impl $test_addr_ip6 -o network_addr_ip6.exe
gcc --std=c99 $impl $test_addr     -o network_addr.exe

gcc --std=c99 $impl $test_tcp_client -o network_tcp_client.exe
gcc --std=c99 $impl $test_tcp_server -o network_tcp_server.exe

gcc --std=c99 $impl $test_udp_client -o network_udp_client.exe
gcc --std=c99 $impl $test_udp_server -o network_udp_server.exe
