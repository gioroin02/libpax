code_core_dir="./code/core/impl"
test_core_dir="./test/core"

base="$code_core_dir/base/export.c"
memory="$code_core_dir/memory/export.c"
string="$code_core_dir/string/export.c"
stream="$code_core_dir/stream/export.c"

test_stream="$test_core_dir/stream/stream.c"

impl="$base $memory $string $stream"

gcc --std=c99 $impl $test_stream -o stream_stream.exe
