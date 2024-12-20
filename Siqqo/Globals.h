#pragma once
#include <vector>
#include <windows.h>
#include <iostream>

namespace Globals {
    extern const COLORREF whiteBorder;
    extern const COLORREF whiteBorder2;
    extern const COLORREF yellowBorder;
    extern const COLORREF redBorder;
    extern const COLORREF msBorder;
    extern const COLORREF bronzeCoinBorder;
    extern const COLORREF high;
    extern const COLORREF middle;
    extern const COLORREF low;
    extern bool Stop;

    enum class MouseEventFlags {
        LEFTDOWN = 0x00000002,
        LEFTUP = 0x00000004,
        RIGHTDOWN = 0x00000008,
        RIGHTUP = 0x00000010
    };


    enum ItemType2
    {
        EMPTY2,
        HIGH,
        MIDDLE,
        LOW,
        BUS2,
        ITEM2
    };

    struct SlotInfo {
        int row;
        int col;
        int x;
        int y;

        SlotInfo(int r, int c, int xPos, int yPos)
            : row(r), col(c), x(xPos), y(yPos) {}
    };

    struct Point {
        int x, y;
        Point(int x, int y) : x(x), y(y) {}
    };


    extern std::vector<SlotInfo> itemSlots;
    extern std::vector<SlotInfo> busSlots;

    extern HHOOK keyboardHook;
    extern HHOOK mouseHook;
}
