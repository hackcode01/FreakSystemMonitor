#include "app/includes/process.hpp"
#include "app/includes/window.hpp"

#include <Windows.h>
#include <iostream>

int32_t WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
                       int32_t numberCmdShow) {
    if (!AllocConsole()) {
        return -1;
    }

    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);

    Process process{};
    DWORD processId{process.getProcessIdByName(L"Lightshot.exe")};
    std::cout << "Process Lightshot.exe with pid " << processId << '\n';
    process.printListProcessThreads(9788);

    Window window{};

    if (!window.createWindow()) {
        exit(EXIT_FAILURE);
    }

    window.runWindow();

    FreeConsole();
    return 0;
}
