impl_dir="./code/impl"
test_dir="./test"

impl_base="$impl_dir/base/export.c"
impl_memory="$impl_dir/memory/export.c"
impl_string="$impl_dir/string/export.c"
impl_stream="$impl_dir/stream/export.c"
impl_format="$impl_dir/format/export.c"
impl_network="$impl_dir/network/export.c"

test_addr_ip4="$test_dir/network/addr_ip4.c"
test_addr_ip6="$test_dir/network/addr_ip6.c"
test_addr="$test_dir/network/addr.c"

test_tcp_client="$test_dir/network/tcp_client.c"
test_tcp_server="$test_dir/network/tcp_server.c"

test_udp_client="$test_dir/network/udp_client.c"
test_udp_server="$test_dir/network/udp_server.c"

impl="$impl_base $impl_memory $impl_string $impl_stream $impl_format $impl_network"

gcc --std=c99 $impl $test_addr_ip4 -o network_addr_ip4.exe
gcc --std=c99 $impl $test_addr_ip6 -o network_addr_ip6.exe
gcc --std=c99 $impl $test_addr     -o network_addr.exe

gcc --std=c99 $impl $test_tcp_client -o network_tcp_client.exe
gcc --std=c99 $impl $test_tcp_server -o network_tcp_server.exe

gcc --std=c99 $impl $test_udp_client -o network_udp_client.exe
gcc --std=c99 $impl $test_udp_server -o network_udp_server.exe
