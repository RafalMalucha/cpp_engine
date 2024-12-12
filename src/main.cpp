#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

static std::vector<std::string> eventLog;

static std::string currentDateTime() {
    std::time_t t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

static void main_window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        std::string timeStr = currentDateTime();

        const char* keyName = glfwGetKeyName(key, scancode);
        
        if (keyName) {
            std::string logEntry = timeStr + " - Key pressed: " + keyName;
            std::cout << logEntry << "\n";
            eventLog.push_back(logEntry);
        } else {
            std::string logEntry = timeStr + " - Key pressed: Unknown or special key (key code: " + std::to_string(scancode) + ")";
            std::cout << logEntry << "\n";
            eventLog.push_back(logEntry);
        }
    }
}

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
    if (!inputMonitorWindow) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(mainWindow);

    // Load OpenGL function pointers with GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    std::cout << "cpp_engine" << "\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

    if (mainWindow){
        std::cout << "mainWindow loaded" << "\n";
    }

    if (inputMonitorWindow){
        std::cout << "inputMonitorWindow loaded" << "\n";
    }

    glfwMakeContextCurrent(mainWindow);
    glfwSwapInterval(1);

    glfwMakeContextCurrent(inputMonitorWindow);
    glfwSwapInterval(1);

    glfwSetKeyCallback(mainWindow, main_window_key_callback);

    // Render loop
    while (!glfwWindowShouldClose(mainWindow) && !glfwWindowShouldClose(inputMonitorWindow)) {
        // Render to first window
        glfwMakeContextCurrent(mainWindow);
        glViewport(0, 0, 1280, 720);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mainWindow);

        // Render to second window
        glfwMakeContextCurrent(inputMonitorWindow);
        glViewport(0, 0, 400, 400);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(inputMonitorWindow);

        // Poll events for both windows
        glfwPollEvents();
    }

    glfwDestroyWindow(mainWindow);
    glfwDestroyWindow(inputMonitorWindow);
    glfwTerminate();
    return 0;
}
