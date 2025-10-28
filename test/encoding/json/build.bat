@echo off

set "code_core_dir=.\code\core\impl"

set "code_encoding_dir=.\code\encoding"
set "test_encoding_dir=.\test\encoding"

set "base=%code_core_dir%\base\export.c"
set "memory=%code_core_dir%\memory\export.c"
set "string=%code_core_dir%\string\export.c"
set "stream=%code_core_dir%\stream\export.c"
set "format=%code_core_dir%\format\export.c"

set "json=%code_encoding_dir%\json\export.c"

set "test_token=%test_encoding_dir%\json\token.c"
set "test_message=%test_encoding_dir%\json\message.c"
set "test_reader=%test_encoding_dir%\json\reader.c"
set "test_writer=%test_encoding_dir%\json\writer.c"

set "impl=%base% %memory% %string% %stream% %format% %json%"

zig cc --std=c99 %impl% %test_token%   -o json_token.exe
zig cc --std=c99 %impl% %test_message% -o json_message.exe
zig cc --std=c99 %impl% %test_reader%  -o json_reader.exe
zig cc --std=c99 %impl% %test_writer%  -o json_writer.exe
