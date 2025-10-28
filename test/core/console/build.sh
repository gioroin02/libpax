code_core_dir="./code/core/impl"
test_core_dir="./test/core"

base="$code_core_dir/base/export.c"
memory="$code_core_dir/memory/export.c"
string="$code_core_dir/string/export.c"
stream="$code_core_dir/stream/export.c"
console="$code_core_dir/console/export.c"

test_mode="$test_core_dir/console/mode.c"

impl="$base $memory $string $stream $console"

gcc --std=c99 $impl $test_mode -o console_mode.exe
