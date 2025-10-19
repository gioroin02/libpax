@echo off

set "impl_dir=.\code\impl"
set "test_dir=.\test"

set "impl_base=%impl_dir%\base\export.c"

set "test_number=%test_dir%\base\number.c"

set "impl=%impl_base%"

zig cc --std=c99 %impl% %test_number% -o base_number.exe
