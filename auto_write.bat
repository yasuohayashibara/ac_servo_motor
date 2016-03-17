//@echo off
setlocal enabledelayedexpansion
taskkill /im ttermpro.exe /f
cd build

rem com port number to connected to the mbed should be maximum
for /f "usebackq tokens=2" %%i in (`mode ^| findstr "COM[0-9]"`) do set RESULT=%%i
set PORT_NAME=%RESULT:COM=%
set PORT_NAME=%PORT_NAME::=%
for /f %%i in ('dir /b /o:d *.hex') do set FILE=%%i
..\lpcsp\lpcsp.exe -c3 -p%PORT_NAME% %FILE%
cd ..

rem change the directory according the install directory of ttpmacro
"C:\\Program Files (x86)\\teraterm\\ttpmacro.exe" %~dp0teraterm\dtr_rts.ttl %PORT_NAME%
endlocal
//@echo on
