@echo off
call clean.bat
if errorlevel 1 exit /b 1
call build.bat
if errorlevel 1 exit /b 1
cls
call start.bat %*