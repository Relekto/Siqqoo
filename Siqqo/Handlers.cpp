#include "Handlers.h"

void Handlers::ScanInventory2() {
    std::cout << "Inventory processing started...\n";

    int startX = 1555; // Top-left X coordinate of the grid
    int startY = 488;  // Top-left Y coordinate of the grid
    int slotWidth = 47, slotHeight = 47; // Slot dimensions
    int horizontalSpacing = 2, verticalSpacing = 2; // Gaps between slots
    int rows = 4, cols = 7; // Grid size
    Globals::itemSlots.clear();
    Globals::busSlots.clear();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Avoid checking (3, 5) and (3, 6)
            if (i == 3 && (j == 5 || j == 6)) continue;

            RECT slotRect = {
                startX + j * (slotWidth + horizontalSpacing),   // Left (X position)
                startY + i * (slotHeight + verticalSpacing),    // Top (Y position)
                startX + j * (slotWidth + horizontalSpacing) + slotWidth,  // Right
                startY + i * (slotHeight + verticalSpacing) + slotHeight   // Bottom
            };


            // Process the slotRect as needed


            // Analyze the slot and identify item type
            Globals::ItemType2 slotType = PixelProcessors::AnalyzeSlot2(slotRect, Globals::whiteBorder, Globals::whiteBorder2, Globals::yellowBorder, Globals::redBorder, Globals::high, Globals::middle,Globals::low);

            // Output the result
            switch (slotType) {
            case Globals::HIGH:
                std::cerr << "High scroll found at [" << i << "," << j << "]\n";
                Globals::busSlots.emplace_back(i, j, slotRect.left + 25, slotRect.top + 25);
                break;
            case Globals::MIDDLE:
                std::cerr << "Middle scroll found at [" << i << "," << j << "]\n";
                Globals::busSlots.emplace_back(i, j, slotRect.left + 25, slotRect.top + 25);
                break;
            case Globals::LOW:
                std::cerr << "Low scroll found at [" << i << "," << j << "]\n";
                Globals::busSlots.emplace_back(i, j, slotRect.left + 25, slotRect.top + 25);
                break;
            case Globals::ITEM2:
                std::cerr << "Item found at [" << i << "," << j << "]\n";
                Globals::itemSlots.emplace_back(i, j, slotRect.left + 25, slotRect.top + 25);
                break;
            }
        }
    }

    std::cout << "Inventory processing completed.\n";

    // Display filled slots for testing
    std::cout << "\nItems Log:\n";
    for (const auto& slot : Globals::itemSlots) {
        std::cout << "Row: " << slot.row << ", Col: " << slot.col
            << " | Coordinates: (" << slot.x << ", " << slot.y << ")\n";
    }
    std::cout << "\nScroll Log:\n";
    for (const auto& slot : Globals::busSlots) {
        std::cout << "Row: " << slot.row << ", Col: " << slot.col
            << " | Coordinates: (" << slot.x << ", " << slot.y << ")\n";
    }
}

void Handlers::HandleAnvil() 
{




    //x - 7 + (row no * 50 : ? 50)	y + 396 + (coll no * 50 : ? 50)
}