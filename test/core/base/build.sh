code_core_dir="./code/core/impl"
test_core_dir="./test/core"

base="$code_core_dir/base/export.c"

test_number="$test_core_dir/base/number.c"

impl="$base"

gcc --std=c99 $impl $test_number -o base_number.exe
