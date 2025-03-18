#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <consoleapi.h>
#endif

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

void closeWindow(GLFWwindow* window, const char* title) {
    if (window) {
        glfwDestroyWindow(window);
        std::cout << "Window closed: " << title << "\n";
    } else {
        std::cerr << "Attempted to close a null window: " << title << "\n";
    }
}