#include "MouseAndKeyboardEvents.h"
#include "Hooks.h"

void MakeConsoleWindowAlwaysOnTop() {
    HWND consoleWindow = GetConsoleWindow();
    if (consoleWindow == NULL) {
        std::cerr << "Failed to get console window handle!\n";
        return;
    }

    if (!SetWindowPos(consoleWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE)) {
        std::cerr << "Failed to set console window on top!\n";
    }
    else {
        std::cout << "Console window is now always on top!\n";
    }
}

int main() {
    MakeConsoleWindowAlwaysOnTop();
    Hooks::SetupHooks();
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(Globals::keyboardHook);
    // UnhookWindowsHookEx(mouseHook);
    return 0;
}