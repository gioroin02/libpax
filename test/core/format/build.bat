@echo off

set "code_core_dir=.\code\core\impl"
set "test_core_dir=.\test\core"

set "base=%code_core_dir%\base\export.c"
set "memory=%code_core_dir%\memory\export.c"
set "string=%code_core_dir%\string\export.c"
set "stream=%code_core_dir%\stream\export.c"
set "format=%code_core_dir%\format\export.c"

set "test_unsigned=%test_core_dir%\format\unsigned.c"
set "test_integer=%test_core_dir%\format\integer.c"
set "test_boolean=%test_core_dir%\format\boolean.c"
set "test_scanner=%test_core_dir%\format\scanner.c"

set "impl=%base% %memory% %string% %stream% %format%"

zig cc --std=c99 %impl% %test_unsigned% -o format_unsigned.exe
zig cc --std=c99 %impl% %test_integer%  -o format_integer.exe
zig cc --std=c99 %impl% %test_boolean%  -o format_boolean.exe
zig cc --std=c99 %impl% %test_scanner%  -o format_scanner.exe
