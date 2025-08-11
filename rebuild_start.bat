@echo off
call build.bat
if errorlevel 1 exit /b 1
cls
call start.bat %*