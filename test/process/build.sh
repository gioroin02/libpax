impl_dir="./code/impl"
test_dir="./test"

impl_base="$impl_dir/base/export.c"
impl_memory="$impl_dir/memory/export.c"
impl_process="$impl_dir/process/export.c"

test_system="$test_dir/process/system.c"
test_channel="$test_dir/process/channel.c"

impl="$impl_base $impl_memory $impl_process"

gcc --std=c99 $impl $test_system  -o process_system.exe
gcc --std=c99 $impl $test_channel -o process_channel.exe
