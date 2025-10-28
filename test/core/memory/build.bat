@echo off

set "code_core_dir=.\code\core\impl"
set "test_core_dir=.\test\core"

set "base=%code_core_dir%\base\export.c"
set "memory=%code_core_dir%\memory\export.c"

set "test_slice=%test_core_dir%\memory\slice.c"
set "test_array=%test_core_dir%\memory\array.c"
set "test_array_ring=%test_core_dir%\memory\array_ring.c"
set "test_system=%test_core_dir%\memory\system.c"

set "impl=%base% %memory%"

zig cc --std=c99 %impl% %test_slice%      -o memory_slice.exe
zig cc --std=c99 %impl% %test_array%      -o memory_array.exe
zig cc --std=c99 %impl% %test_array_ring% -o memory_array_ring.exe
zig cc --std=c99 %impl% %test_system%     -o memory_system.exe
