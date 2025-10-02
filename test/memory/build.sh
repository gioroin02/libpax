impl_dir="./code/impl"
test_dir="./test"

impl_base="$impl_dir/base/export.c"
impl_memory="$impl_dir/memory/export.c"

test_slice="$test_dir/memory/slice.c"
test_array="$test_dir/memory/array.c"
test_array_ring="$test_dir/memory/array_ring.c"
test_system="$test_dir/memory/system.c"

impl="$impl_base $impl_memory"

gcc --std=c99 $impl $test_slice      -o memory_slice.exe
gcc --std=c99 $impl $test_array      -o memory_array.exe
gcc --std=c99 $impl $test_array_ring -o memory_array_ring.exe
gcc --std=c99 $impl $test_system     -o memory_system.exe
