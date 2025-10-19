code_core_dir="./code/core/impl"
code_encoding_dir="./code/encoding"

test_encoding_dir="./test/encoding"

base="$code_core_dir/base/export.c"
memory="$code_core_dir/memory/export.c"
string="$code_core_dir/string/export.c"
stream="$code_core_dir/stream/export.c"
format="$code_core_dir/format/export.c"

json="$code_encoding_dir/json/export.c"

test_token="$test_encoding_dir/json/token.c"
test_message="$test_encoding_dir/json/message.c"
test_reader="$test_encoding_dir/json/reader.c"

impl="$base $memory $string $stream $format $json"

gcc --std=c99 $impl $test_token   -o json_token.exe
gcc --std=c99 $impl $test_message -o json_message.exe
gcc --std=c99 $impl $test_reader  -o json_reader.exe
