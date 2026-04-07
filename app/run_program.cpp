#include "app/includes/process.hpp"
#include "app/includes/thread.hpp"
#include "app/includes/window.hpp"

#include <cstdlib>
#include <iostream>

int32_t WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
                       int32_t numberCmdShow) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    if (!AllocConsole()) {
        return EXIT_FAILURE;
    }

    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);

    Process process{};

    DWORD processId{process.getProcessIdByName(L"Code.exe")};
    std::cout << "Process " << process.getProcessName().c_str() << " with pid " << processId << '\n';
    process.printListProcessThreads(processId);

    std::cout << '\n';
    process.setProcessName(L"Code.exe");
    Thread::printAllThreads(process);

    Window window{};

    if (!window.createWindow()) {
        exit(EXIT_FAILURE);
    }

    window.runWindow();

    FreeConsole();
    return EXIT_SUCCESS;
}
