@echo off

set "impl_dir=.\code\impl"
set "test_dir=.\test"

set "impl_base=%impl_dir%\base\export.c"
set "impl_memory=%impl_dir%\memory\export.c"
set "impl_string=%impl_dir%\string\export.c"
set "impl_stream=%impl_dir%\stream\export.c"
set "impl_storage=%impl_dir%\storage\export.c"

set "test_directory=%test_dir%\storage\directory.c"
set "test_path=%test_dir%\storage\path.c"
set "test_read=%test_dir%\storage\read.c"
set "test_destroy=%test_dir%\storage\destroy.c"

set "impl=%impl_base% %impl_memory% %impl_string% %impl_stream% %impl_storage%"

zig cc --std=c99 %impl% %test_directory% -o storage_directory.exe
zig cc --std=c99 %impl% %test_path%      -o storage_path.exe
zig cc --std=c99 %impl% %test_read%      -o storage_read.exe
zig cc --std=c99 %impl% %test_destroy%   -o storage_destroy.exe
