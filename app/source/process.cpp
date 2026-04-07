#include "app/includes/process.hpp"

#include <iostream>
#include <memory>
#include <TlHelp32.h>

Process::Process(std::string processName)
    : m_processName{processName} {}

Process::Process(DWORD pid)
    : m_pid{pid} {}

Process::Process(std::string processName, DWORD pid)
    : m_processName{processName}, m_pid{pid} {}

void Process::setProcessName(const WCHAR* processName, u32 codePage) {
    if (!processName) {
        std::cerr << __FUNCTION__
                  << " function failed because the process name passed is null in line: "
                  << __LINE__ << '\n';
        return;
    }

    i32 length{WideCharToMultiByte(codePage, 0, processName, -1, nullptr, 0, nullptr, nullptr)};
    if (length <= 0) {
        DWORD error{GetLastError()};
        std::cerr << __FUNCTION__
                  << " function returned an error: " << error << " in line: "
                  << __LINE__ << '\n';
        return;
    }

    std::string result(length - 1, '\0');
    if (WideCharToMultiByte(codePage, 0, processName, -1, &result[0], length, nullptr, nullptr) == 0) {
        std::cerr << __FUNCTION__
                  << " function returned with conversion error in line: "
                  << __LINE__ << '\n';
        return;
    }

    m_processName = std::move(result);
}

DWORD Process::getProcessIdByName(const std::wstring& processName) const {
    DWORD processId{0};
    HANDLE hSnapshot{CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)};
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PROCESSENTRY32W processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32W);

    if (Process32FirstW(hSnapshot, &processEntry)) {
        do {
            if (_wcsicmp(processName.c_str(), processEntry.szExeFile) == 0) {
                processId = processEntry.th32ProcessID;
                break;
            }
        } while (Process32NextW(hSnapshot, &processEntry));
    }

    CloseHandle(hSnapshot);
    return processId;
}

void Process::printListProcessThreads(DWORD processId) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Error " << __FUNCTION__ << " function a " << GetLastError() << '\n';
        return;
    }

    THREADENTRY32 threadEntry{};
    threadEntry.dwSize = sizeof(THREADENTRY32);

    if (Thread32First(hSnapshot, &threadEntry)) {
        std::cout << "Threads for process ID: " << processId << '\n';

        while (Thread32Next(hSnapshot, &threadEntry)) {
            if (threadEntry.th32OwnerProcessID == processId) {
                std::cout << "TID: " << threadEntry.th32ThreadID << '\n';
            }
        }
    } else {
        std::cerr << __FUNCTION__ << "function returned error Thread32First: "
                  << GetLastError() << " in line: " << __LINE__ << '\n';
        return;
    }

    CloseHandle(hSnapshot);
}
