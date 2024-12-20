#include "Controls.h"

bool Controls::isInventoryOpened() {
    COLORREF targetColor = RGB(228, 223, 143);
    POINT minPoint = { 1684, 162 };
    POINT maxPoint = { 1744, 187 };
    Globals::Point result{ 1,1 };
    PixelProcessors::findPixelOnScreen(minPoint, maxPoint, targetColor, result);
    if (result.x != 150 && result.y != 900)
    {
        std::cout << "Inventory is open. " << result.x << "," << result.y << std::endl;
        return true;
    }

    else
        return false;
}

Globals::Point Controls::isMenuOpened()
{
    COLORREF targetColor = RGB(211, 114, 4);
    POINT minPoint = { 550,251 };
    POINT maxPoint = { 1407,712 };
    Globals::Point result{ 1,1 };
    PixelProcessors::findPixelOnScreen(minPoint, maxPoint, targetColor, result);
    if (result.x != 150 && result.y != 900)
    {
        std::cout << "Menu is opened. " << result.x << "," << result.y << std::endl;      
        return result;
    }
    else
        return result;
}

Globals::Point Controls::isMagicAnvilOpened()
{
    POINT minPoint = { 176, 96 };
    POINT maxPoint = { 1765, 1025 };
    COLORREF targetColor = RGB(199, 175, 60);
    Globals::Point result(1, 1);
    PixelProcessors::findPixelOnScreen(minPoint, maxPoint, targetColor, result);
    if (result.x != 150 && result.y != 900)
    {
        std::cout << "Anvil Opened at. " << result.x << "," << result.y << std::endl;
        return result;
    }
    else
        return result;
}

