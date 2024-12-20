#include "MouseAndKeyboardEvents.h"
#include <windows.h>

void MouseAndKeyboardEvents::MouseMove(int x, int y) {
    Utility::Wait(50);
    SetCursorPos(x, y);
}
void MouseAndKeyboardEvents::LeftMouseClick(int x, int y) {
    Utility::Wait(50);
    SetCursorPos(x, y);
    Utility::Wait(50);
    mouse_event(static_cast<DWORD>(Globals::MouseEventFlags::LEFTDOWN), x, y, 0, 0);
    Utility::Wait(50);
    mouse_event(static_cast<DWORD>(Globals::MouseEventFlags::LEFTUP), x, y, 0, 0);
}
void MouseAndKeyboardEvents::RightMouseClick(int x, int y) {
    Utility::Wait(50);
    SetCursorPos(x, y);
    Utility::Wait(50);
    mouse_event(static_cast<DWORD>(Globals::MouseEventFlags::RIGHTDOWN), x, y, 0, 0);
    Utility::Wait(50);
    mouse_event(static_cast<DWORD>(Globals::MouseEventFlags::RIGHTUP), x, y, 0, 0);
}
void MouseAndKeyboardEvents::LeftMouseDragDrop(int posx, int posy, int destx, int desty) {
    Utility::Wait(200);
    SetCursorPos(posx, posy);
    Utility::Wait(200);
    mouse_event(static_cast<DWORD>(Globals::MouseEventFlags::LEFTDOWN), posx, posy, 0, 0);
    Utility::Wait(200);
    SetCursorPos(destx, desty);
    Utility::Wait(200);
    mouse_event(static_cast<DWORD>(Globals::MouseEventFlags::LEFTUP), destx, desty, 0, 0);
}
void MouseAndKeyboardEvents::SendKeyEvent(UINT keyCode, bool keyDown) {
    if (keyDown) {
        keybd_event(keyCode, 0, 0, 0); // Key down
        Utility::Wait(50);
    }
    else {
        keybd_event(keyCode, 0, KEYEVENTF_KEYUP, 0); // Key up
        Utility::Wait(50);
    }
}