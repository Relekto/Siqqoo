#include "Hooks.h"
std::thread processThread;
LRESULT CALLBACK Hooks::KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
        switch (kbdStruct->vkCode) {
        case VK_F4: {
            if (processThread.joinable()) {
                std::cout << "F4 Pressed - Process Already Running" << std::endl;
            }
            else {
                std::cout << "F4 Pressed - Process is Starting" << std::endl;
                Globals::Stop = false; // Ensure Stop is reset
                processThread = std::thread(MainLoop::startProcess);
            }
            break;
        }
        case VK_F5: {
            std::cout << "F5 Pressed - Process is Stopping" << std::endl;
            Globals::Stop = true;
            if (processThread.joinable()) {
                processThread.join();
                std::cout << "Process Stopped" << std::endl;
            }
            break;
        }
        default:
            break;
        }
    }
    return CallNextHookEx(Globals::keyboardHook, nCode, wParam, lParam);
}

// Hook Setup
void Hooks::SetupHooks() {
    Globals::keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);
    //mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, NULL, 0);

    if (!Globals::keyboardHook) {
        std::cerr << "Failed to install hooks!" << std::endl;
        exit(1);
    }
    std::cout << "Hooks installed.\n";
}



//// Mouse Hook Callback
//LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
//    if (nCode >= 0) {
//        MSLLHOOKSTRUCT* mouseStruct = (MSLLHOOKSTRUCT*)lParam;
//        if ((mouseStruct->flags & LLMHF_INJECTED) != 0)
//        {
//            //mouseStruct->flags -= LLMHF_INJECTED;
//            //std::cout << "flag cleared" << std::endl;
//        }
//
//        if (wParam == WM_LBUTTONDOWN) {
//            std::cout << "Mouse Left Button Down at: X=" << mouseStruct->pt.x << ", Y=" << mouseStruct->pt.y << std::endl;
//        }
//        else if (wParam == WM_RBUTTONDOWN) {
//            std::cout << "Mouse Right Button Down at: X=" << mouseStruct->pt.x << ", Y=" << mouseStruct->pt.y << std::endl;
//        }
//    }
//    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
//}