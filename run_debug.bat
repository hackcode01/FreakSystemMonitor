@echo off
setlocal EnableDelayedExpansion

.\build_debug\Debug\FreakSystemMonitor.exe

echo.
echo =====================================================
echo Program FreakSystemMonitor returned code %errorlevel%
echo =====================================================

endlocal
