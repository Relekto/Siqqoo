#include "Openers.h"

bool Openers::OpenInventory()
{
    int retryCount = 0;
    int maxRetries = 5;
    while (retryCount < maxRetries)
    {
        MouseAndKeyboardEvents::LeftMouseClick(1696, 1057);
        Utility::Wait(350);
        if (Controls::isInventoryOpened()) {
            return true;
        }
        Utility::Wait(1000);
        retryCount++;
    }
    std::cerr << "Failed to open inv after " << maxRetries << " attempts." << std::endl;
    return false;
}

void Openers::CloseInventory()
{
    MouseAndKeyboardEvents::LeftMouseClick(1884, 169);
}


bool Openers::OpenAnvilMenu()
{

    int retryCount = 0;
    int maxRetries = 5;
    Globals::Point xy{ 150,900 };
    while (retryCount < maxRetries)
    {
        MouseAndKeyboardEvents::LeftMouseClick(1043, 453);
        MouseAndKeyboardEvents::RightMouseClick(1043, 453);
        Utility::Wait(100);
        xy = Controls::isMenuOpened();
        if (xy.x != 150 && xy.y != 900) {
            MouseAndKeyboardEvents::LeftMouseClick(xy.x - 140, xy.y + 100);
            return true;
        }
        Utility::Wait(1000);
        retryCount++;
    }
    std::cerr << "Failed to open menu after " << maxRetries << " attempts.\n";
    return false;
}
