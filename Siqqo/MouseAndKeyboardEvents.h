#pragma once
#include "Utility.h"
#include "Globals.h"


namespace MouseAndKeyboardEvents {
    void MouseMove(int x, int y);
    void LeftMouseClick(int x, int y);
    void RightMouseClick(int x, int y);
    void LeftMouseDragDrop(int posx, int posy, int destx, int desty);
    void SendKeyEvent(UINT keyCode, bool keyDown);
}