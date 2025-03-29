#include <gtest/gtest.h>
#include "Utils.h"

TEST(UtilsTest, CurrentDateTimeFormat) {
    std::string now = currentDateTime();
    ASSERT_EQ(now.length(), 19);
}
