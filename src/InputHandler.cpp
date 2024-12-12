#include "InputHandler.h"
#include <iostream>
#include "Utils.h"

std::vector<std::string> eventLog;

void main_window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        std::string timeStr = currentDateTime();
        const char* keyName = glfwGetKeyName(key, scancode);

        if (keyName) {
            std::string logEntry = timeStr + " - Key pressed: " + keyName;
            std::cout << logEntry << "\n";
            eventLog.push_back(logEntry);
        } else {
            std::string logEntry = timeStr + " - Key pressed: Unknown or special key (key code: " + std::to_string(scancode) + ")";
            std::cout << logEntry << "\n";
            eventLog.push_back(logEntry);
        }
    }
}