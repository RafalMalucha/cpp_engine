#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <fmt/core.h>

#ifdef __linux__

#include <cstdlib>
#include <cstring>
#include <unistd.h>

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

#endif


void setupOpenGL() {
    float vertices[] = {
        -0.5f,  0.5f, 0.0f,  // Top Left (0)
        -0.5f, -0.5f, 0.0f,  // Bottom Left (1)
         0.5f, -0.5f, 0.0f,  // Bottom Right (2)
         0.5f,  0.25f, 0.0f   // Top Right (3)
    };

    unsigned int indices[] = {
        0, 1, 2,  // First Triangle (Top Left, Bottom Left, Bottom Right)
        0, 2, 3   // Second Triangle (Top Left, Bottom Right, Top Right)
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shaderProgram = loadShaders("vertex_shader.glsl", "fragment_shader.glsl");
}

int main() {

    fmt::print("FMT {}!\n", "test");

    #ifdef __linux__

    launchNewTerminalOnLinux();

    #endif

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    };

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

    setupOpenGL();

    while (!glfwWindowShouldClose(mainWindow)) {
        // Render to main window
        glfwMakeContextCurrent(mainWindow);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);  
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    closeWindow(mainWindow, "cpp_engine");
    std::cout << "cpp_engine closed" << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    glfwTerminate();
    return 0;
}