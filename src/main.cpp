#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* mainWindow = glfwCreateWindow(1280, 720, "cpp_engine", NULL, NULL);
    if (!mainWindow) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    GLFWwindow* inputMonitorWindow = glfwCreateWindow(400, 400, "cpp_engine_input_monitor", NULL, NULL);

    glfwMakeContextCurrent(mainWindow);

    // Load OpenGL function pointers with GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Check OpenGL info
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

    // Render loop
    while (!glfwWindowShouldClose(mainWindow)) {
        // Process input
        if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mainWindow, true);

        // Render something - for now just clear the screen
        glClearColor(0.5f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and poll IO events
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();

        // Process input
        if (glfwGetKey(inputMonitorWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(inputMonitorWindow, true);

        // Render something - for now just clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and poll IO events
        glfwSwapBuffers(inputMonitorWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
