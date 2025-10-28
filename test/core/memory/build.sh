code_core_dir="./code/core/impl"
test_core_dir="./test/core"

base="$code_core_dir/base/export.c"
memory="$code_core_dir/memory/export.c"

test_slice="$test_core_dir/memory/slice.c"
test_array="$test_core_dir/memory/array.c"
test_array_ring="$test_core_dir/memory/array_ring.c"
test_system="$test_core_dir/memory/system.c"

impl="$base $memory"

gcc --std=c99 $impl $test_slice      -o memory_slice.exe
gcc --std=c99 $impl $test_array      -o memory_array.exe
gcc --std=c99 $impl $test_array_ring -o memory_array_ring.exe
gcc --std=c99 $impl $test_system     -o memory_system.exe
