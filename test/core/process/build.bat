@echo off

set "impl_dir=.\code\impl"
set "test_dir=.\test"

set "impl_base=%impl_dir%\base\export.c"
set "impl_memory=%impl_dir%\memory\export.c"
set "impl_process=%impl_dir%\process\export.c"

set "test_system=%test_dir%\process\system.c"
set "test_channel=%test_dir%\process\channel.c"

set "impl=%impl_base% %impl_memory% %impl_process%"

zig cc --std=c99 %impl% %test_system%  -o process_system.exe
zig cc --std=c99 %impl% %test_channel% -o process_channel.exe
