impl_dir="./code/impl"
test_dir="./test"

impl_base="$impl_dir/base/export.c"
impl_memory="$impl_dir/memory/export.c"
impl_string="$impl_dir/string/export.c"
impl_stream="$impl_dir/stream/export.c"
impl_storage="$impl_dir/storage/export.c"

test_directory="$test_dir/storage/directory.c"
test_path="$test_dir/storage/path.c"
test_read="$test_dir/storage/read.c"
test_destroy="$test_dir/storage/destroy.c"

impl="$impl_base $impl_memory $impl_string $impl_stream $impl_storage"

gcc --std=c99 $impl $test_directory -o storage_directory.exe
gcc --std=c99 $impl $test_path      -o storage_path.exe
gcc --std=c99 $impl $test_read      -o storage_read.exe
gcc --std=c99 $impl $test_destroy   -o storage_destroy.exe
