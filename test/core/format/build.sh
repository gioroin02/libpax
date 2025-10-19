impl_dir="./code/impl"
test_dir="./test"

impl_base="$impl_dir/base/export.c"
impl_memory="$impl_dir/memory/export.c"
impl_string="$impl_dir/string/export.c"
impl_stream="$impl_dir/stream/export.c"
impl_format="$impl_dir/format/export.c"

test_unsigned="$test_dir/format/unsigned.c"
test_integer="$test_dir/format/integer.c"
test_boolean="$test_dir/format/boolean.c"
test_scanner="$test_dir/format/scanner.c"

impl="$impl_base $impl_memory $impl_string $impl_stream $impl_format"

gcc --std=c99 $impl $test_unsigned -o format_unsigned.exe
gcc --std=c99 $impl $test_integer  -o format_integer.exe
gcc --std=c99 $impl $test_boolean  -o format_boolean.exe
gcc --std=c99 $impl $test_scanner  -o format_scanner.exe
