@echo off

set "code_core_dir=.\code\core\impl"
set "test_core_dir=.\test\core"

set "base=%code_core_dir%\base\export.c"
set "memory=%code_core_dir%\memory\export.c"
set "string=%code_core_dir%\string\export.c"
set "display=%code_core_dir%\display\export.c"

set "process=%code_core_dir%\process\export.c"

set "test_display=%test_core_dir%\display\display.c"

set "impl=%base% %memory% %string% %display% %process%"

set "lib=-lgdi32"
@rem set "lib=-lgdi32 -Wl,--subsystem,windows"

zig cc --std=c99 %impl% %test_display% %lib% -o display_display.exe
