#include "includes/main_window.hpp"

int32_t WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
                       int32_t numberCmdShow) {
    MainWindow app{};
    if (!app.create()) {
        return -1;
    }

    app.runMessageLoop();

    return 0;
}
