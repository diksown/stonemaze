#include "utils.h"

#include <chrono>
#include <thread>

void nap(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
