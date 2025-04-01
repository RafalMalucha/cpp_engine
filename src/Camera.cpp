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
    static bool firstMouse = true;
    static double lastX = 0.0f;
    static double lastY = 0.0f;

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos - lastX);
    float yoffset = static_cast<float>(lastY - ypos); // reversed y

    lastX = xpos;
    lastY = ypos;

    xoffset *= Sensitivity;
    yoffset *= Sensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    // clamp
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
