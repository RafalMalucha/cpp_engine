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
#include "WindowCallbacks.h"
#include "Skybox.h"

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

    Skybox skybox;
    std::vector<std::string> faces = {
        "assets/textures/skybox/right.bmp",
        "assets/textures/skybox/left.bmp",
        "assets/textures/skybox/top.bmp",
        "assets/textures/skybox/bottom.bmp",
        "assets/textures/skybox/front.bmp",
        "assets/textures/skybox/back.bmp"
    };

    Model model("assets/models/Subaru/scene.gltf");

    skybox.init(faces);

    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(mainWindow, &camera);

    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

    glfwSetCursorPosCallback(mainWindow, mouse_callback);

    glfwSetKeyCallback(mainWindow, main_window_key_callback);

    setupOpenGL(shaderProgram);

    glfwSwapInterval(0);

    while (!glfwWindowShouldClose(mainWindow)) {

        float fps = calculateFPS();
        std::string title = fmt::format("cpp_engine - FPS: {:.2f}", fps);
        glfwSetWindowTitle(mainWindow, title.c_str());

        renderFrame(mainWindow, shaderProgram, model, camera, skybox);
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
