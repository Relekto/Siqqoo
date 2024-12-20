#include "Utility.h"
#include <thread>

void Utility::Wait(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}