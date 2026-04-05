#include "app/includes/window.hpp"

#include <iostream>

Window::Window(i32 width, i32 height, const std::wstring& title)
    : m_width{width}, m_height{height}, m_title{title} {}

Window::Window() {}

Window::~Window() {
    if (m_hwnd) {
        DestroyWindow(m_hwnd);
    }
}

bool Window::registerClass() {
    WNDCLASSEX wndClass{};
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.lpfnWndProc = getWindowProcStatic;
    wndClass.hInstance = GetModuleHandle(nullptr);
    wndClass.lpszClassName = m_className;
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wndClass)) {
        if (GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
            std::cout << __FUNCTION__ << " function returned with LastError(): "
                      << GetLastError() << "in line: " << __LINE__ << '\n'
                      << "Class already exists.\n";

            return false;
        }
    }

    return true;
}

bool Window::createWindow() {
    if (!registerClass()) {
        return false;
    }

    m_hwnd = CreateWindowEx(
        0,
        m_className,
        m_title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        this
    );

    if (!m_hwnd) {
        std::cerr << __FUNCTION__ << " function. m_hwnd must be not null. Line: "
                  << __LINE__ << '\n';
        return false;
    }

    centerWindow();
    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);

    return true;
}

void Window::centerWindow() {
    if (!m_hwnd) {
        std::cerr << __FUNCTION__ << " function. m_hwnd must be not null. Line: "
                  << __LINE__ << '\n';
        return;
    }

    i32 screenWidth{GetSystemMetrics(SM_CXSCREEN)};
    i32 screenHeight{GetSystemMetrics(SM_CYSCREEN)};

    RECT rect{};
    GetWindowRect(m_hwnd, &rect);
    i32 windowWidth{rect.right - rect.left};
    i32 windowHeight{rect.bottom - rect.top};

    i32 x{(screenWidth - windowWidth) / 2};
    i32 y{(screenHeight - windowHeight) / 2};

    SetWindowPos(m_hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Window::runWindow() {
    MSG message{};
    while (GetMessage(&message, nullptr, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

LRESULT CALLBACK Window::getWindowProcStatic(HWND hwnd, u32 uMessage,
                                             WPARAM wParam, LPARAM lParam) {
    Window* p_window{nullptr};

    if (uMessage == WM_NCCREATE) {
        CREATESTRUCT* p_create{reinterpret_cast<CREATESTRUCT*>(lParam)};
        p_window = static_cast<Window*>(p_create->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p_window));
        p_window->m_hwnd = hwnd;
    } else {
        p_window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (p_window) {
        return p_window->getWindowProc(hwnd, uMessage, wParam, lParam);
    } else {
        return DefWindowProc(hwnd, uMessage, wParam, lParam);
    }
}

LRESULT Window::getWindowProc(HWND hwnd, u32 uMessage, WPARAM wParam, LPARAM lParam) {
    switch (uMessage) {
        case WM_PAINT: {
            PAINTSTRUCT paintStruct{};
            HDC hdc{BeginPaint(hwnd, &paintStruct)};
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            onPaint(hdc, clientRect);
            EndPaint(hwnd, &paintStruct);

            return 0;
        }

        case WM_SIZE: {
            i32 width{LOWORD(lParam)};
            i32 height{HIWORD(lParam)};
            onResize(width, height);

            return 0;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);

            return 0;
        }

        default: {
            return onMessage(uMessage, wParam, lParam);
        }
    }
}

void Window::onPaint(HDC hdc, RECT& clientRect) {
    std::wstring text{L"Hello, Windows!"};
    SetBkMode(hdc, TRANSPARENT);
    DrawTextW(hdc, text.c_str(), -1, &clientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void Window::onResize(i32 width, i32 height) {
    InvalidateRect(m_hwnd, nullptr, TRUE);
}

LRESULT Window::onMessage(u32 uMessage, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(m_hwnd, uMessage, wParam, lParam);
}
