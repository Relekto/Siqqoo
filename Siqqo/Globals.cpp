#include "Globals.h"

namespace Globals {
    const COLORREF whiteBorder = RGB(214, 207, 199);
    const COLORREF whiteBorder2 = RGB(137, 137, 136);
    const COLORREF yellowBorder = RGB(252, 253, 1);
    const COLORREF redBorder = RGB(172, 49, 48);
    const COLORREF msBorder = RGB(106, 153, 178);
    const COLORREF bronzeCoinBorder = RGB(17, 51, 0);
    const COLORREF high = RGB(255, 238, 204);
    const COLORREF middle = RGB(254, 34, 16);
    const COLORREF low = RGB(84, 35, 34);
    bool Stop = false;


    std::vector<SlotInfo> itemSlots;
    std::vector<SlotInfo> busSlots;
    HHOOK keyboardHook = NULL;
    HHOOK mouseHook = NULL;
}
