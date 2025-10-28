@echo off

set "code_core_dir=.\code\core\impl"
set "test_core_dir=.\test\core"

set "base=%code_core_dir%\base\export.c"
set "memory=%code_core_dir%\memory\export.c"
set "string=%code_core_dir%\string\export.c"

set "test_buffer8=%test_core_dir%\string\buffer8.c"
set "test_buffer16=%test_core_dir%\string\buffer16.c"
set "test_buffer32=%test_core_dir%\string\buffer32.c"
set "test_string8=%test_core_dir%\string\string8.c"
set "test_string16=%test_core_dir%\string\string16.c"
set "test_string32=%test_core_dir%\string\string32.c"
set "test_convert=%test_core_dir%\string\convert.c"

set "impl=%base% %memory% %string%"

zig cc --std=c99 %impl% %test_buffer8%  -o string_buffer8.exe
zig cc --std=c99 %impl% %test_buffer16% -o string_buffer16.exe
zig cc --std=c99 %impl% %test_buffer32% -o string_buffer32.exe
zig cc --std=c99 %impl% %test_string8%  -o string_string8.exe
zig cc --std=c99 %impl% %test_string16% -o string_string16.exe
zig cc --std=c99 %impl% %test_string32% -o string_string32.exe
zig cc --std=c99 %impl% %test_convert%  -o string_convert.exe
