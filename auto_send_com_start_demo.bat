//@echo off
setlocal enabledelayedexpansion
taskkill /im ttpmacro.exe /f
taskkill /im ttermpro.exe /f

rem change the directory according the install directory of ttpmacro
start "C:\\Program Files (x86)\\teraterm\\ttpmacro.exe" %~dp0teraterm\send_com_start_demo.ttl
endlocal
//@echo on
