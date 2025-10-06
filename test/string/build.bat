@echo off

set "impl_dir=.\code\impl"
set "test_dir=.\test"

set "impl_base=%impl_dir%\base\export.c"
set "impl_memory=%impl_dir%\memory\export.c"
set "impl_string=%impl_dir%\string\export.c"

set "test_buffer8=%test_dir%\string\buffer8.c"
set "test_string8=%test_dir%\string\string8.c"

set "impl=%impl_base% %impl_memory% %impl_string%"

zig cc --std=c99 %impl% %test_buffer8% -o string_buffer8.exe
zig cc --std=c99 %impl% %test_string8% -o string_string8.exe
