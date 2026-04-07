@echo off
setlocal EnableDelayedExpansion

echo ======================================
echo Building FreakSystemMonitor (Debug)...
echo ======================================

cmake --build build_debug --config Debug
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Build exists with error!
    pause
    exit /b -1
)

echo.
echo [SUCCESS] Build is completed
echo Executable file: build_debug/Debug/FreakSystemMonitor.exe

endlocal
