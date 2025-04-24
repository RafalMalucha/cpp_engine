#pragma once 
#include <chrono>

namespace Time {
    using clock = std::chrono::steady_clock;

    void init();

    double frameTime();
}