impl_dir="./code/impl"
test_dir="./test"

impl_base="$impl_dir/base/export.c"

test_number="$test_dir/base/number.c"

impl="$impl_base"

gcc --std=c99 $impl $test_number -o base_number.exe
