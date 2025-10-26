code_core_dir="./code/core/impl"
test_core_dir="./test/core"

base="$code_core_dir/base/export.c"
memory="$code_core_dir/memory/export.c"
string="$code_core_dir/string/export.c"
display="$code_core_dir/display/export.c"

process="$code_core_dir/process/export.c"

test_display="$test_core_dir/display/display.c"

impl="$base $memory $string $display $process"

lib="-lX11 -DPAX_DISPLAY_XORG"

gcc --std=c99 $impl $test_display $lib -o display_display.exe
