@echo off

set "impl_dir=.\code\impl"
set "test_dir=.\test"

set "impl_base=%impl_dir%\base\export.c"
set "impl_memory=%impl_dir%\memory\export.c"
set "impl_string=%impl_dir%\string\export.c"
set "impl_stream=%impl_dir%\stream\export.c"
set "impl_console=%impl_dir%\console\export.c"

set "test_mode=%test_dir%\console\mode.c"

set "impl=%impl_base% %impl_memory% %impl_string% %impl_stream% %impl_console%"

zig cc --std=c99 %impl% %test_mode% -o console_mode.exe
