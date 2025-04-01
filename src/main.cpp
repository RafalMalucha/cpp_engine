#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <fmt/core.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef __linux__

#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <signal.h>

#endif

#include "WindowManager.h"
#include "InputHandler.h"
#include "ShaderLoader.h"
#include "OpenGLSetup.h"
#include "Utils.h"
#include "Renderer.h"
#include "Camera.h"

unsigned int VAO;   // Vertex Array Object
unsigned int VBO;   // Vertex Buffer Object
unsigned int EBO;   // Element Buffer Object
unsigned int shaderProgram;

int main() {

    #ifdef __linux__

    launchNewTerminalOnLinux();

    #endif

    GLFWwindow* mainWindow = initializeEngineWindow();
    if (!mainWindow) {
        return -1;
    }

    Camera camera;

    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(mainWindow, &camera);

    glfwSetCursorPosCallback(mainWindow, mouse_callback);

    glfwSetKeyCallback(mainWindow, main_window_key_callback);

    setupOpenGL(VAO, VBO, EBO, shaderProgram);

    glfwSwapInterval(0);

    while (!glfwWindowShouldClose(mainWindow)) {

        float fps = calculateFPS();
        std::string title = fmt::format("cpp_engine - FPS: {:.2f}", fps);
        glfwSetWindowTitle(mainWindow, title.c_str());

        renderFrame(mainWindow, shaderProgram, VAO, camera);
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    closeWindow(mainWindow, "cpp_engine");
    std::cout << "cpp_engine closed" << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    glfwTerminate();

    #ifdef __linux__

    closeTerminalOnLinux();

    #endif

    return 0;
}
