@echo off

set "impl_dir=.\code\impl"
set "test_dir=.\test"

set "impl_base=%impl_dir%\base\export.c"
set "impl_memory=%impl_dir%\memory\export.c"
set "impl_string=%impl_dir%\string\export.c"
set "impl_stream=%impl_dir%\stream\export.c"
set "impl_format=%impl_dir%\format\export.c"

set "test_unsigned=%test_dir%\format\unsigned.c"
set "test_integer=%test_dir%\format\integer.c"
set "test_boolean=%test_dir%\format\boolean.c"

set "impl=%impl_base% %impl_memory% %impl_string% %impl_stream% %impl_format%"

zig cc --std=c99 %impl% %test_unsigned% -o format_unsigned.exe
zig cc --std=c99 %impl% %test_integer%  -o format_integer.exe
zig cc --std=c99 %impl% %test_boolean%  -o format_boolean.exe
