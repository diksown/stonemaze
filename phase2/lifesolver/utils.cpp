#include "utils.h"

#include <chrono>
#include <thread>

void sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
