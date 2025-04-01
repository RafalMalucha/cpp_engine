#include "InputHandler.h"
#include <iostream>
#include <unordered_map>
#include <functional>
#include "Utils.h"
#include "Camera.h"

std::vector<std::string> eventLog;

std::unordered_map<int, std::function<void()>> keyBindings;

void main_window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    static double lastX = 0.0;
    static double lastY = 0.0;
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera) {
        camera->handleInput(window);
    }
}
