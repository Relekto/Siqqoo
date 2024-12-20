#include "MainLoop.h"
#include "Hooks.h"
void MainLoop::startProcess()
{
	int repeat = 0;
	std::cout << "Please enter the number of times to repeat ";
	std::cin >> repeat;
	for (int i = 0; i < repeat; i++)
	{
		Openers::OpenInventory();
		Handlers::ScanInventory2();
		Openers::CloseInventory();
		Openers::OpenAnvilMenu();
		Globals::Point xy = Controls::isMagicAnvilOpened();
		while (xy.x == 150 && xy.y == 900)
		{
			xy = Controls::isMagicAnvilOpened();
		}
		int j = 0;
		j = Globals::itemSlots.size();
		auto& slot = Globals::itemSlots.front();
		for (int i = 0; i < j; i++)
		{
			slot = Globals::itemSlots.front();
			std::cout << "Clicking item at (" << slot.row << ", " << slot.col
				<< ") | Screen coordinates: (" << xy.x - 41 + (slot.col * 50) << ", " << xy.y + 398 + (slot.row * 50) << ")\n";
			MouseAndKeyboardEvents::RightMouseClick(xy.x - 41 + (slot.col * 50), xy.y + 398 + (slot.row * 50));
			std::cout << "Clicking Scroll at " << " | Screen coordinates : (" << xy.x - 41 + (Globals::busSlots.front().col * 50) << ", " << xy.y + 398 + (Globals::busSlots.front().row * 50) << ")\n";
			MouseAndKeyboardEvents::RightMouseClick(xy.x - 41 + (Globals::busSlots.front().col * 50), xy.y + 398 + (Globals::busSlots.front().row * 50));
			std::cout << "Clicking 1st Confirm at " << " | Screen coordinates : (" << xy.x + 33 << ", " << xy.y + 398 + xy.y + 306 << ")\n";
			MouseAndKeyboardEvents::LeftMouseClick(xy.x + 33, xy.y + 306);
			std::cout << "Clicking 2nd Confirm at " << " | Screen coordinates : (" << xy.x + 29 << ", " << xy.y + 378 << ")\n";
			MouseAndKeyboardEvents::LeftMouseClick(xy.x + 29, xy.y + 378);
			Globals::itemSlots.erase(Globals::itemSlots.begin());
			std::cout << "\nClosing inventory " << " | Screen coordinates : (" << xy.x + 285 << ", " << xy.y + 10 << ")\n";
			MouseAndKeyboardEvents::LeftMouseClick(xy.x + 285, xy.y + 10);
			xy = { 150,900 };
			std::cout << "\nRe-Opening Anvil\n";
			Openers::OpenAnvilMenu();
			xy = Controls::isMagicAnvilOpened();
			while (xy.x == 150 && xy.y == 900)
			{
				xy = Controls::isMagicAnvilOpened();
			}
		}

		std::cout << "\nFinished "<< i+1<< ". Cycle\n";
	}
	
}
