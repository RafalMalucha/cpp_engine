#include "systems/Time.h"
#include <iostream>

namespace Time {
    static clock::time_point last;

    int tickCounter = 0;

    void init() {
        last = clock::now();
    }

    double frameTime() {
        auto now = clock::now();
        double dt = std::chrono::duration<double>(now - last).count();
        last = now;
        return dt;
    }
}