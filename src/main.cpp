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

unsigned int VAO;   // Vertex Array Object
unsigned int VBO;   // Vertex Buffer Object
unsigned int EBO;   // Element Buffer Object
unsigned int shaderProgram;

int main() {

    #ifdef __linux__

    launchNewTerminalOnLinux();

    #endif

    fmt::print("FMT works\n");

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    };
    fmt::print("GLFW works\n");

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    if (!primary) {
        std::cerr << "Failed to get primary monitor.\n";
        return -1;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    if (!mode) {
        std::cerr << "Failed to get video mode.\n";
        return -1;
    }

    std::cout << "Primary Monitor Resolution: " << mode->width << "x" << mode->height << "\n";

    std::cout << "Target cpp_engine window resolution: " << (mode->width / 3 * 2) << "x" << (mode->height / 3 * 2) << "\n";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::cout << "cpp_engine loaded" << "\n";

    GLFWwindow* mainWindow = createWindow((mode->width / 3 * 2), (mode->height / 3 * 2), "cpp_engine");
    if (!mainWindow) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(mainWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }
    fmt::print("GLAD works\n");

    glfwSetKeyCallback(mainWindow, main_window_key_callback);

    setupOpenGL(VAO, VBO, EBO, shaderProgram);

    while (!glfwWindowShouldClose(mainWindow)) {
        // Render to main window
        glfwMakeContextCurrent(mainWindow);

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glm::mat4 model = glm::rotate(
            glm::mat4(1.7f),
            (float)glfwGetTime(), // rotates over time
            glm::vec3(-2.0f, 2.0f, 5.0f) // axis of rotation
        );
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

        // get uniform locations
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc  = glGetUniformLocation(shaderProgram, "view");
        unsigned int projLoc  = glGetUniformLocation(shaderProgram, "projection");

        // set uniforms
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);  // why? america explain???

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
