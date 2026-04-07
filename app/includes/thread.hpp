#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include "process.hpp"

class Thread {

public:
    Thread() = default;

    Thread(const Process& process, DWORD threadId);

    constexpr DWORD getThreadId() const noexcept {
        return m_threadId;
    }

    const std::string& getProcessName() const noexcept {
        return m_processName;
    }

    static void printAllThreads(const Process& process);

private:
    DWORD m_threadId{};
    std::string m_processName{};
};

#endif
