#ifndef __PROCESS_HPP__
#define __PROCESS_HPP__

#include "app/defines.hpp"

#include <Windows.h>
#include <string>

class Process {

public:
    Process() = default;

    Process(std::string processName);
    Process(DWORD pid);
    Process(std::string processName, DWORD pid);

    DWORD getProcessIdByName(const std::wstring& processName) const;
    void printListProcessThreads(DWORD processId);

    const std::string& getProcessName() const noexcept { return m_processName; }

    void setProcessName(const WCHAR* processName, u32 codePage = CP_UTF8);

private:

    std::string m_processName{};
    DWORD m_pid{};
};

#endif
