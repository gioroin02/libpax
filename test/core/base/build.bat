@echo off

set "code_core_dir=.\code\core\impl"
set "test_core_dir=.\test\core"

set "base=%code_core_dir%\base\export.c"

set "test_number=%test_core_dir%\base\number.c"

set "impl=%base%"

zig cc --std=c99 %impl% %test_number% -o base_number.exe
