code_core_dir="./code/core/impl"
test_core_dir="./test/core"

base="$code_core_dir/base/export.c"
memory="$code_core_dir/memory/export.c"
string="$code_core_dir/string/export.c"
stream="$code_core_dir/stream/export.c"
storage="$code_core_dir/storage/export.c"

test_directory="$test_core_dir/storage/directory.c"
test_path="$test_core_dir/storage/path.c"
test_read="$test_core_dir/storage/read.c"
test_destroy="$test_core_dir/storage/destroy.c"

impl="$base $memory $string $stream $storage"

gcc --std=c99 $impl $test_directory -o storage_directory.exe
gcc --std=c99 $impl $test_path      -o storage_path.exe
gcc --std=c99 $impl $test_read      -o storage_read.exe
gcc --std=c99 $impl $test_destroy   -o storage_destroy.exe
