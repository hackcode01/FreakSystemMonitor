@echo off
setlocal EnableDelayedExpansion

echo ========================================
echo Initialize FreakSystemMonitor (Debug)...
echo ========================================

cmake -S . -B build_debug
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] CMake configure exists with error!
    pause
    exit /b -1
)

echo.
echo [SUCCESS] Project is initialized
echo Project directory: build_debug

endlocal
