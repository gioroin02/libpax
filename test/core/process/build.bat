@echo off

set "code_core_dir=.\code\core\impl"
set "test_core_dir=.\test\core"

set "base=%code_core_dir%\base\export.c"
set "memory=%code_core_dir%\memory\export.c"
set "process=%code_core_dir%\process\export.c"

set "test_system=%test_core_dir%\process\system.c"
set "test_channel=%test_core_dir%\process\channel.c"
set "test_pool=%test_core_dir%\process\pool.c"

set "impl=%base% %memory% %process%"

zig cc --std=c99 %impl% %test_system%  -o process_system.exe
zig cc --std=c99 %impl% %test_channel% -o process_channel.exe
zig cc --std=c99 %impl% %test_pool%    -o process_pool.exe
