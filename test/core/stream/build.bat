@echo off

set "code_core_dir=.\code\core\impl"
set "test_core_dir=.\test\core"

set "base=%code_core_dir%\base\export.c"
set "memory=%code_core_dir%\memory\export.c"
set "string=%code_core_dir%\string\export.c"
set "stream=%code_core_dir%\stream\export.c"

set "test_stream=%test_core_dir%\stream\stream.c"

set "impl=%base% %memory% %string% %stream%"

zig cc --std=c99 %impl% %test_stream% -o stream_stream.exe
