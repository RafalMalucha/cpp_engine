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

unsigned int VAO;   // Vertex Array Object
unsigned int VBO;   // Vertex Buffer Object
unsigned int EBO;   // Element Buffer Object
unsigned int shaderProgram;

#ifdef __linux__

void launchNewTerminalOnLinux() {
    if (isatty(STDIN_FILENO)) {
        return;
    }

    std::cout << "Launching in a new terminal...\n";

    char execPath[1024];
    ssize_t len = readlink("/proc/self/exe", execPath, sizeof(execPath) - 1);
    if (len != -1) {
        execPath[len] = '\0';

        std::string command = "x-terminal-emulator -e bash -c \"" + std::string(execPath) + "; exec bash\" &";
        system(command.c_str());

        exit(0);
    } else {
        std::cerr << "Error: Could not determine executable path.\n";
    }
}

void closeTerminalOnLinux() {
    if (isatty(STDIN_FILENO)) {
        std::cout << "Closing terminal...\n";
        // Send SIGHUP to the parent shell (usually the terminal emulator)
        pid_t parentPid = getppid();
        kill(parentPid, SIGHUP);
        exit(0);
    }
}

#endif


void setupOpenGL() {
    float vertices[] = {
        // Face: Front (+Z)
        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Bottom-left
         0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Bottom-right
         0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Top-right
        -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Top-left

        // Face: Back (-Z)
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

        // Face: Left (-X)
        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,

        // Face: Right (+X)
         0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,

        // Face: Top (+Y)
        -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,

        // Face: Bottom (-Y)
        -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f
    };

    unsigned int indices[] = {
        // Front
        0, 1, 2,
        0, 2, 3,

        // Back
        4, 5, 6,
        4, 6, 7,

        // Left
        8, 9,10,
        8,10,11,

        // Right
       12,13,14,
       12,14,15,

        // Top
       16,17,18,
       16,18,19,

        // Bottom
       20,21,22,
       20,22,23
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
    glEnableVertexAttribArray(1);

    shaderProgram = loadShaders("vertex_shader.glsl", "fragment_shader.glsl");

    glUseProgram(shaderProgram);
    glUniform3f(glGetUniformLocation(shaderProgram, "lightDir"), 1.0f, 1.0f, 2.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.8f, 0.2f, 0.2f);
}

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::cout << "cpp_engine loaded" << "\n";

    GLFWwindow* mainWindow = createWindow(1920, 1080, "cpp_engine");
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

    setupOpenGL();

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
