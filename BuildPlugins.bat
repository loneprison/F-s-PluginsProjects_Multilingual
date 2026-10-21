@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0_tools\BuildPlugins.ps1" %*
exit /b %errorlevel%
