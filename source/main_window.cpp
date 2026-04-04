#include "includes/main_window.hpp"

#include <string>
#include <iostream>

const wchar_t* MainWindow::m_className = L"MainWindowClass";

MainWindow::MainWindow()
    : m_hwnd{nullptr} {

    std::cout << "Hello, World!";
}

MainWindow::~MainWindow() {
    if (m_hwnd) {
        DestroyWindow(m_hwnd);
    }
}

bool MainWindow::create() {
    WNDCLASS wndClass{};
    wndClass.lpfnWndProc = windowProc;
    wndClass.hInstance = GetModuleHandle(nullptr);
    wndClass.lpszClassName = reinterpret_cast<LPCWSTR>(m_className);
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wndClass);

    int32_t width{800};
    int32_t height{400};
    m_hwnd = CreateWindowEx(
        0,
        reinterpret_cast<LPCWSTR>(m_className),
        reinterpret_cast<LPCWSTR>(L"MainWindow"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, GetModuleHandle(nullptr), this
    );

    if (!m_hwnd) {
        return false;
    }

    centerWindow();
    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);

    return true;
}

void MainWindow::centerWindow() {
    if (!m_hwnd) {
        return;
    }

    int32_t screenWidth{GetSystemMetrics(SM_CXSCREEN)};
    int32_t screenHeight{GetSystemMetrics(SM_CYSCREEN)};

    RECT rect{};
    GetWindowRect(m_hwnd, &rect);
    int32_t winWidth{rect.right - rect.left};
    int32_t winHeight{rect.bottom - rect.top};

    int32_t x{(screenWidth - winWidth) / 2};
    int32_t y{(screenHeight - winHeight) / 2};

    SetWindowPos(m_hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void MainWindow::runMessageLoop() {
    MSG message{};
    while (GetMessage(&message, nullptr, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

LRESULT CALLBACK MainWindow::windowProc(HWND hwnd, UINT uMessage, WPARAM wParam,
                                        LPARAM lParam) {
    MainWindow* pThis{nullptr};

    if (uMessage == WM_NCCREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = static_cast<MainWindow*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        pThis->m_hwnd = hwnd;
    } else {
        pThis = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pThis) {
        return pThis->handleMessage(uMessage, wParam, lParam);
    } else {
        return DefWindowProc(hwnd, uMessage, wParam, lParam);
    }
}

LRESULT MainWindow::handleMessage(UINT uMessage, WPARAM wParam, LPARAM lParam) {
    switch (uMessage) {
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        default: {
            return DefWindowProc(m_hwnd, uMessage, wParam, lParam);
        }
    }
}
