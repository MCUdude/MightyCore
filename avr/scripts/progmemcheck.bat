@echo off
REM Windows batch file equivalent of progmemcheck.sh
REM Checks if PROGMEM section is too large (over 65535 bytes)
REM Usage: progmemcheck.bat <objdump_tool> <object_file>

if "%1"=="" goto usage
if "%2"=="" goto usage

REM Execute objdump command and extract the address (should be decimal with -t d option)
for /f "tokens=1" %%i in ('%1 -t d %2 ^| findstr "__ctors_start"') do set progmem_end=%%i

REM Check if we got a result
if "%progmem_end%"=="" (
    exit /b 0
)

REM Remove any leading/trailing spaces
set progmem_end=%progmem_end: =%

REM Remove leading zeros manually (batch treats leading zeros as octal)
:strip_zeros
if "%progmem_end:~0,1%"=="0" if not "%progmem_end%"=="0" (
    set progmem_end=%progmem_end:~1%
    goto strip_zeros
)

REM If we stripped all digits, it was "000..." so set to 0
if "%progmem_end%"=="" set progmem_end=0

REM Check if progmem_end is greater than 65535
if %progmem_end% LEQ 65535 goto end

REM Calculate the excess bytes
set /a excess=%progmem_end% - 65535

REM Display warning message
echo.
echo _______________________________________________________________
echo ^| Severe Warning: PROGMEM section too large by %excess% bytes.            ^|
echo ^| Your program will most probably be unstable!                ^|
echo ^| Use the macro PROGMEM_FAR from ^<progmem_far.h^> and          ^|
echo ^| pgm_get_far_address/pgm_read_xxxx_far from ^<avr/pgmspace.h^>.^|
echo ^|_____________________________________________________________^|
echo.
goto end

:usage
echo Usage: %0 ^<objdump_tool^> ^<object_file^>
echo Example: %0 avr-objdump firmware.elf
exit /b 1

:end
exit /b 0
