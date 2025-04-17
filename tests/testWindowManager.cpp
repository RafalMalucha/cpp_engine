#include <gtest/gtest.h>

#include "platform/WindowManager.h"

TEST(WindowManagerTest, initializeEngineWindow_check) {
    GLFWwindow* window = initializeEngineWindow();
    ASSERT_NE(window, nullptr);
}

TEST(WindowManagerTest, getPrimaryMonitor_test) {

    GLFWmonitor* primary = getPrimaryMonitor();
    ASSERT_NE(primary, nullptr);
}

TEST(WindowManagerTest, calculateWindowResolution_test) {
    GLFWmonitor* primary = getPrimaryMonitor();
    auto [width, height] = calculateWindowResolution(primary);
    ASSERT_GT(width, 0);
    ASSERT_GT(height, 0);
}

// clean up after tests

TEST(WindowManagerTest, cleanUp) {
    glfwTerminate();
}