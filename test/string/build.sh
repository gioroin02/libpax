impl_dir="./code/impl"
test_dir="./test"

impl_base="$impl_dir/base/export.c"
impl_memory="$impl_dir/memory/export.c"
impl_string="$impl_dir/string/export.c"

test_buffer8="$test_dir/string/buffer8.c"
test_string8="$test_dir/string/string8.c"

impl="$impl_base $impl_memory $impl_string"

gcc --std=c99 $impl $test_buffer8 -o string_buffer8.exe
gcc --std=c99 $impl $test_string8 -o string_string8.exe
