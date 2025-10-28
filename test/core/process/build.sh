code_core_dir="./code/core/impl"
test_core_dir="./test/core"

base="$code_core_dir/base/export.c"
memory="$code_core_dir/memory/export.c"
process="$code_core_dir/process/export.c"

test_system="$test_core_dir/process/system.c"
test_channel="$test_core_dir/process/channel.c"
test_pool="$test_core_dir/process/pool.c"

impl="$base $memory $process"

gcc --std=c99 $impl $test_system  -o process_system.exe
gcc --std=c99 $impl $test_channel -o process_channel.exe
gcc --std=c99 $impl $test_pool    -o process_pool.exe
