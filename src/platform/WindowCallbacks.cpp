#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowCallbacks.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    std::cout << "[Window] Framebuffer resized: " << width << "x" << height << "\n";
}
