#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include "WindowManager.h"
#include "InputHandler.h"

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::cout << "cpp_engine loaded" << "\n";

    GLFWwindow* mainWindow = createWindow(1280, 720, "cpp_engine");
    if (!mainWindow) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(mainWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glfwSetKeyCallback(mainWindow, main_window_key_callback);

    while (!glfwWindowShouldClose(mainWindow)) {
        // Render to main window
        glfwMakeContextCurrent(mainWindow);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mainWindow);

        glfwPollEvents();
    }

    closeWindow(mainWindow, "cpp_engine");
    std::cout << "cpp_engine closed" << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    glfwTerminate();
    return 0;
}