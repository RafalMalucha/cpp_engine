#include "Camera.h"
#include <iostream>

Camera::Camera()
    : position(0.0f, 0.0f, 5.0f),
      target(0.0f, 0.0f, 0.0f),
      up(0.0f, 1.0f, 0.0f) {}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, target, up);
}

void Camera::handleInput(GLFWwindow* window) {
    glm::vec3 direction = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(direction, up));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += direction;
        std::cout << "W" << "\n";
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= direction;
        std::cout << "S" << "\n";
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right;
        std::cout << "A" << "\n";
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right;
        std::cout << "D" << "\n";
    }
}
