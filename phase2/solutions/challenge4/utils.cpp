#include "utils.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

void nap(double sleepTimSeconds) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds((int)(sleepTimSeconds * 1000)));
}

void warn(const std::string& msg) {
    std::string warnMsg =
        std::string("\033[31m") + msg + std::string("\033[0m");
    std::cerr << warnMsg << std::endl;
}