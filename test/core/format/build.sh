code_core_dir="./code/core/impl"
test_core_dir="./test/core"

base="$code_core_dir/base/export.c"
memory="$code_core_dir/memory/export.c"
string="$code_core_dir/string/export.c"
stream="$code_core_dir/stream/export.c"
format="$code_core_dir/format/export.c"

test_unsigned="$test_core_dir/format/unsigned.c"
test_integer="$test_core_dir/format/integer.c"
test_boolean="$test_core_dir/format/boolean.c"
test_scanner="$test_core_dir/format/scanner.c"

impl="$base $memory $string $stream $format"

gcc --std=c99 $impl $test_unsigned -o format_unsigned.exe
gcc --std=c99 $impl $test_integer  -o format_integer.exe
gcc --std=c99 $impl $test_boolean  -o format_boolean.exe
gcc --std=c99 $impl $test_scanner  -o format_scanner.exe
