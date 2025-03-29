#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <consoleapi.h>
#endif

#include "WindowManager.h"
#include <iostream>
#include <fmt/core.h>


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

GLFWwindow* initializeEngineWindow() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return nullptr;
    }
    fmt::print("GLFW works\n");

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    if (!primary) {
        std::cerr << "Failed to get primary monitor.\n";
        return nullptr;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    if (!mode) {
        std::cerr << "Failed to get video mode.\n";
        return nullptr;
    }

    std::cout << "Primary Monitor Resolution: " << mode->width << "x" << mode->height << "\n";

    std::cout << "Target cpp_engine window resolution: " << (mode->width / 3) * 2 << "x" << (mode->height / 3) * 2 << "\n";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::cout << "cpp_engine loaded" << "\n";

    GLFWwindow* window = createWindow((mode->width / 3) * 2, (mode->height / 3) * 2, "cpp_engine");
    if (!window) {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return nullptr;
    }

    fmt::print("GLAD works\n");

    return window;
}