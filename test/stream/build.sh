impl_dir="./code/impl"
test_dir="./test"

impl_base="$impl_dir/base/export.c"
impl_memory="$impl_dir/memory/export.c"
impl_string="$impl_dir/string/export.c"
impl_stream="$impl_dir/stream/export.c"

test_stream="$test_dir/stream/stream.c"

impl="$impl_base $impl_memory $impl_string $impl_stream"

zig cc --std=c99 $impl $test_stream -o stream_stream.exe
