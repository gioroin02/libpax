@echo off

set "impl_dir=.\code\impl"
set "test_dir=.\test"

set "impl_base=%impl_dir%\base\export.c"
set "impl_memory=%impl_dir%\memory\export.c"
set "impl_string=%impl_dir%\string\export.c"
set "impl_stream=%impl_dir%\stream\export.c"

set "test_stream=%test_dir%\stream\stream.c"

set "impl=%impl_base% %impl_memory% %impl_string% %impl_stream%"

zig cc --std=c99 %impl% %test_stream% -o stream_stream.exe
