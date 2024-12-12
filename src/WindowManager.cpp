#include "WindowManager.h"
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* createWindow(int width, int height, const char* title) {
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window: " << title << "\n";
    }
    std::cout << "Window loaded: " << title << "\n";
    return window;
}