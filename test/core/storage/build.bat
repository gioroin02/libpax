@echo off

set "code_core_dir=.\code\core\impl"
set "test_core_dir=.\test\core"

set "base=%code_core_dir%\base\export.c"
set "memory=%code_core_dir%\memory\export.c"
set "string=%code_core_dir%\string\export.c"
set "stream=%code_core_dir%\stream\export.c"
set "storage=%code_core_dir%\storage\export.c"

set "test_directory=%test_core_dir%\storage\directory.c"
set "test_path=%test_core_dir%\storage\path.c"
set "test_read=%test_core_dir%\storage\read.c"
set "test_destroy=%test_core_dir%\storage\destroy.c"

set "impl=%base% %memory% %string% %stream% %storage%"

zig cc --std=c99 %impl% %test_directory% -o storage_directory.exe
zig cc --std=c99 %impl% %test_path%      -o storage_path.exe
zig cc --std=c99 %impl% %test_read%      -o storage_read.exe
zig cc --std=c99 %impl% %test_destroy%   -o storage_destroy.exe
