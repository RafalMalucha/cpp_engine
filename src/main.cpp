#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <fmt/core.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#ifdef __linux__

#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <signal.h>

#endif

#include "platform/WindowManager.h"
#include "platform/InputHandler.h"
#include "platform/WindowCallbacks.h"
#include "rendering/Camera.h"
#include "rendering/Renderer.h"
#include "rendering/Skybox.h"
#include "rendering/ShaderLoader.h"
#include "rendering/OpenGLSetup.h"
#include "utils/Utils.h"
#include "scene/Scene.h"

unsigned int shaderProgram;

int main() {

    #ifdef __linux__

    launchNewTerminalOnLinux();

    #endif

    GLFWwindow* mainWindow = initializeEngineWindow();
    if (!mainWindow) {
        return -1;
    }

    glfwMakeContextCurrent(mainWindow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(mainWindow, false);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    Scene currentScene;

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

    skybox.init(faces);

    auto carObject = currentScene.createGameObject("Car");
    carObject->setModel(std::make_shared<Model>("assets/models/car/scene.gltf"));

    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(mainWindow, &camera);

    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

    glfwSetCursorPosCallback(mainWindow, mouse_callback);
    glfwSetKeyCallback(mainWindow, main_window_key_callback);
    glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
    glfwSetScrollCallback(mainWindow, scroll_callback);

    setupOpenGL(shaderProgram);

    glfwSwapInterval(0);

    while (!glfwWindowShouldClose(mainWindow)) {

        glfwPollEvents();

        float fps = calculateFPS();
        std::string title = fmt::format("cpp_engine - FPS: {:.2f}", fps);
        glfwSetWindowTitle(mainWindow, title.c_str());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Editor");
        ImGui::Text("ImGui is working");
        ImGui::End();

        renderFrame(mainWindow, shaderProgram, currentScene, camera, skybox);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mainWindow);
    }

    closeWindow(mainWindow, "cpp_engine");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    std::cout << "cpp_engine closed" << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    glfwTerminate();

    #ifdef __linux__

    closeTerminalOnLinux();

    #endif

    return 0;
}
