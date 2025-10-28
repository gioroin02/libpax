code_core_dir="./code/core/impl"
test_core_dir="./test/core"

base="$code_core_dir/base/export.c"
memory="$code_core_dir/memory/export.c"
string="$code_core_dir/string/export.c"

test_buffer8="$test_core_dir/string/buffer8.c"
test_buffer16="$test_core_dir/string/buffer16.c"
test_buffer32="$test_core_dir/string/buffer32.c"
test_string8="$test_core_dir/string/string8.c"
test_string16="$test_core_dir/string/string16.c"
test_string32="$test_core_dir/string/string32.c"
test_convert="$test_core_dir/string/convert.c"

impl="$base $memory $string"

gcc --std=c99 $impl $test_buffer8  -o string_buffer8.exe
gcc --std=c99 $impl $test_buffer16 -o string_buffer16.exe
gcc --std=c99 $impl $test_buffer32 -o string_buffer32.exe
gcc --std=c99 $impl $test_string8  -o string_string8.exe
gcc --std=c99 $impl $test_string16 -o string_string16.exe
gcc --std=c99 $impl $test_string32 -o string_string32.exe
gcc --std=c99 $impl $test_convert  -o string_convert.exe
