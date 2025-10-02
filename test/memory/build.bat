@echo off

set "impl_dir=.\code\impl"
set "test_dir=.\test"

set "impl_base=%impl_dir%\base\export.c"
set "impl_memory=%impl_dir%\memory\export.c"

set "test_slice=%test_dir%\memory\slice.c"
set "test_array=%test_dir%\memory\array.c"
set "test_array_ring=%test_dir%\memory\array_ring.c"
set "test_system=%test_dir%\memory\system.c"

set "impl=%impl_base% %impl_memory%"

zig cc --std=c99 %impl% %test_slice%      -o memory_slice.exe
zig cc --std=c99 %impl% %test_array%      -o memory_array.exe
zig cc --std=c99 %impl% %test_array_ring% -o memory_array_ring.exe
zig cc --std=c99 %impl% %test_system%     -o memory_system.exe
