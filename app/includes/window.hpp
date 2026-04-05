#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include "app/defines.hpp"

#include <Windows.h>
#include <string>

class Window {

public:
    Window();
    Window(i32 width, i32 height, const std::wstring& title);

    virtual ~Window();

    bool createWindow();

    void runWindow();

    HWND getHandle() const {
        return m_hwnd;
    }

protected:
    virtual void onPaint(HDC hdc, RECT& clientRect);
    virtual void onResize(i32 width, i32 height);
    virtual LRESULT onMessage(u32 uMessage, WPARAM wParam, LPARAM lParam);

private:
    HWND m_hwnd{nullptr};
    std::wstring m_title{L"Window"};
    i32 m_width{1000};
    i32 m_height{600};
    static constexpr wchar_t* m_className{L"Window"};

    static LRESULT CALLBACK getWindowProcStatic(HWND hwnd, u32 uMessage,
                                                WPARAM wParam, LPARAM lParam);

    LRESULT getWindowProc(HWND hwnd, u32 uMessage, WPARAM wParam, LPARAM lParam);

    void centerWindow();
    bool registerClass();
};

#endif
