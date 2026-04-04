#ifndef __MAIN_WINDOW_HPP__
#define __MAIN_WINDOW_HPP__

#include <Windows.h>
#include <cstdint>

class MainWindow {

public:
    MainWindow();
    ~MainWindow();

    bool create();
    void runMessageLoop();

private:
    HWND m_hwnd{};
    static const wchar_t* m_className;

    static LRESULT CALLBACK windowProc(HWND hwnd, UINT uMessage, WPARAM wParam,
                                       LPARAM lParam);
    LRESULT handleMessage(UINT uMessage, WPARAM wParam, LPARAM lParam);
    void centerWindow();
};

#endif
