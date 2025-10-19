impl_dir="./code/impl"
test_dir="./test"

impl_base="$impl_dir/base/export.c"
impl_memory="$impl_dir/memory/export.c"
impl_string="$impl_dir/string/export.c"
impl_stream="$impl_dir/stream/export.c"
impl_console="$impl_dir/console/export.c"

test_mode="$test_dir/console/mode.c"

impl="$impl_base $impl_memory $impl_string $impl_stream $impl_console"

gcc --std=c99 $impl $test_mode -o console_mode.exe
