#include "app/includes/thread.hpp"

#include <iostream>
#include <TlHelp32.h>

Thread::Thread(const Process& process, DWORD threadId)
    : m_threadId{threadId}, m_processName{process.getProcessName()} {}

void Thread::printAllThreads(const Process& process) {
    const std::string& processName{process.getProcessName()};
    if (processName.empty()) {
#if defined(_DEBUG)
        std::cerr << __FUNCTION__
                  << " function failed because the process name is empty "
                     "(cannot resolve PID) in line: " << __LINE__ << '\n';
#endif
        return;
    }

    u32 codePage{CP_UTF8};
    i32 length{MultiByteToWideChar(codePage, 0, processName.c_str(), -1, nullptr, 0)};
    if (length <= 0) {
#if defined(_DEBUG)
        std::cerr << __FUNCTION__
                  << " function returned error: " << GetLastError()
                  << " in line: " << __LINE__ << ". Length of processName must be > 0.\n";
#endif
        return;
    }

    std::wstring wname(length - 1, L'\0');
    if (MultiByteToWideChar(codePage, 0, processName.c_str(), -1, &wname[0], length) == 0) {
#if defined(_DEBUG)
        std::cerr << __FUNCTION__
                  << " function exit with error: "
                     "MultiByteToWideChar conversion error in line: " << __LINE__ << '\n';
#endif
        return;
    }

    DWORD processId{process.getProcessIdByName(wname)};
    if (processId == 0) {
#if defined(_DEBUG)
        std::cerr << __FUNCTION__
                  << " function could not resolve PID for process name: "
                  << processName << " in line: " << __LINE__ << '\n';
#endif
        return;
    }

    HANDLE hSnapshot{CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0)};
    if (hSnapshot == INVALID_HANDLE_VALUE) {
#if defined(_DEBUG)
        std::cerr << "Error " << __FUNCTION__ << " CreateToolhelp32Snapshot failed: "
              << GetLastError() << "in line: " << __LINE__ << '\n';
#endif
        return;
    }

    THREADENTRY32 threadEntry{};
    threadEntry.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hSnapshot, &threadEntry)) {
#if defined(_DEBUG)
        std::cerr << __FUNCTION__ << " function exit with Thread32First failed: "
                  << GetLastError() << " in line: " << __LINE__ << '\n';
#endif
        CloseHandle(hSnapshot);
        return;
    }

    std::cout << "Threads for process ID: " << processId << " (name: "
              << processName << ")\n";

    do {
        if (threadEntry.th32OwnerProcessID == processId) {
            std::cout << "TID: " << threadEntry.th32ThreadID << '\n';
        }
    } while (Thread32Next(hSnapshot, &threadEntry));

    CloseHandle(hSnapshot);
}
