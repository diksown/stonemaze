#include "utils.h"

#include <chrono>
#include <thread>

void nap(int sleepTimeMs) {
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMs));
}
