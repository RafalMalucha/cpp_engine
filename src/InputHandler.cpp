#include "InputHandler.h"
#include <iostream>
#include <unordered_map>
#include <functional>
#include "Utils.h"
#include "Camera.h"

std::vector<std::string> eventLog;

std::unordered_map<int, std::function<void()>> keyBindings;

void main_window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods, Camera camera) {
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

        camera.handleInput(window);
    } else if (action == GLFW_RELEASE) {
        std::string timeStr = currentDateTime();
        const char* keyName = glfwGetKeyName(key, scancode);

        if (keyName) {
            std::string logEntry = timeStr + " - Key released: " + keyName;
            std::cout << logEntry << "\n";
            eventLog.push_back(logEntry);
        } else {
            std::string logEntry = timeStr + " - Key released: Unknown or special key (key code: " + std::to_string(scancode) + ")";
            std::cout << logEntry << "\n";
            eventLog.push_back(logEntry);
        }
    }
}
