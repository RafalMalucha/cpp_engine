#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "utils/Utils.h"

TEST(UtilsTest, CurrentDateTimeFormat) {
    std::string now = currentDateTime();
    ASSERT_EQ(now.length(), 19);
}

TEST(UtilsTest, calculateFPS_ReturnsValidFloat) {
    float fps = calculateFPS();

    // Just make sure it's a float and not NaN/Inf
    ASSERT_TRUE(std::isfinite(fps)) << "FPS is not finite (was NaN or Inf)";
    SUCCEED() << "calculateFPS() returned: " << fps;
}
