#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
    : Position(0.0f, 0.0f, 5.0f),
      WorldUp(0.0f, 1.0f, 0.0f),
      Yaw(-90.0f), 
      Pitch(0.0f),
      Sensitivity(0.1f)
{
    updateVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::handleInput(GLFWwindow* window) {
    if (!isMouseLocked) return;  // skip processing if mouse is free

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        return;
    }

    float xoffset = static_cast<float>(xpos - lastX);
    float yoffset = static_cast<float>(lastY - ypos); // reversed Y

    lastX = xpos;
    lastY = ypos;

    xoffset *= Sensitivity;
    yoffset *= Sensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    // Clamp
    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    updateVectors();
}

void Camera::updateVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    newFront.y = sin(glm::radians(Pitch));
    newFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(newFront);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}

void Camera::lockMouse(GLFWwindow* window) {
    if (isMouseLocked) {
        glfwGetCursorPos(window, &savedX, &savedY);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        isMouseLocked = false;
        std::cout << "Mouse unlocked at (" << savedX << ", " << savedY << ")\n";
    } else {
        // Re-lock the mouse (DO NOT set cursor pos, GLFW will ignore it)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        isMouseLocked = true;
        firstMouse = true;  // prevent big delta on first move
        std::cout << "Mouse re-locked\n";
    }
}
