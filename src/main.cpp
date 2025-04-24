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
#include "rendering/ShaderLoader.h"
#include "rendering/OpenGLSetup.h"
#include "utils/Utils.h"
#include "scene/Scene.h"
#include "scene/Skybox.h"
#include "scene/SceneSaver.h"
#include "scene/SceneLoader.h"
#include "scene/SceneManager.h"
#include "scene/GameObjectManager.h"
#include "systems/Time.h"

unsigned int shaderProgram;

bool isWireframe = false;
bool isModelOne = true;
static std::shared_ptr<GameObject> gSelectedObj; 
static bool show_object_manager = false;
int tickCounter = 0;

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

    Scene currentScene = sceneLoader("assets/scenes/emptyScene.json");

    Camera camera;

    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(mainWindow, &camera);

    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

    glfwSetCharCallback(mainWindow, char_callback);
    glfwSetCursorPosCallback(mainWindow, mouse_callback);
    glfwSetKeyCallback(mainWindow, main_window_key_callback);
    glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
    glfwSetScrollCallback(mainWindow, scroll_callback);

    setupOpenGL(shaderProgram);

    glfwSwapInterval(0);

    Time::init();

    const double fixedDt    = 1.0 / 64.0;    // logic tick-rate (e.g. 64 Hz)
    double       accumulator = 0.0;

    while (!glfwWindowShouldClose(mainWindow)) {

        double frameDt = Time::frameTime();

        accumulator += frameDt;

        while (accumulator >= fixedDt) {
            std::cout << "tick: " << tickCounter << std::endl;
            tickCounter++;
            accumulator -= fixedDt;
        }

        glfwPollEvents();

        float fps = calculateFPS();
        std::string title = fmt::format("cpp_engine - FPS: {:.2f}", fps);
        glfwSetWindowTitle(mainWindow, title.c_str());

        

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        sceneManager(currentScene);

        ImGui::Begin("Editor");
        for (const auto& obj : currentScene.getAllGameObjects()) {
            if (ImGui::Button(obj->getName().c_str())) {

                gSelectedObj = obj; 
                show_object_manager = true; 

                std::cout << "-----------------" << std::endl;
                std::cout << "Transform.position" << std::endl;
                std::cout << obj->getTransform().position[0] << " x " << obj->getTransform().position[1] << " y " << obj->getTransform().position[2] << " z " <<  std::endl;

                std::cout << "-----------------" << std::endl;
                std::cout << "Transform.rotation" << std::endl;
                std::cout << obj->getTransform().rotation[0] << " x " << obj->getTransform().rotation[1] << " y " << obj->getTransform().rotation[2] << " z " <<  std::endl;

                std::cout << "-----------------" << std::endl;
                std::cout << "Transform.scale" << std::endl;
                std::cout << obj->getTransform().scale[0] << " x " << obj->getTransform().scale[1] << " y " << obj->getTransform().scale[2] << " z " <<  std::endl;

                std::cout << "-----------------" << std::endl;
                std::cout << "Transform.scale" << std::endl;
                printMatrix(obj->getTransform().getMatrix());

                std::cout << "-----------------------------------------------------------------------" << std::endl;
            }
        }
        if (ImGui::Button("Toggle Wireframe")) {
            isWireframe = !isWireframe;

            if (isWireframe) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
        ImGui::End();


        if (show_object_manager)                          
        {
            //ImGui::Begin("Gizmo controls", &show_object_manager); 
            gameObjectManager(gSelectedObj, &show_object_manager);
        }

        renderFrame(mainWindow, shaderProgram, currentScene, camera);

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
