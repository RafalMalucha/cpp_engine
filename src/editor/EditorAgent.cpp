#include "EditorAgent.h"
#include <glm/gtc/matrix_transform.hpp>

EditorAgent::EditorAgent(Camera* camera) 
    : camera(camera) {}

void EditorAgent::setMoveSpeed(float speed) {
    moveSpeed = speed;
}

void EditorAgent::handleInput(GLFWwindow* window, float deltaTime) {
    glm::vec3& pos      = camera->Position;
    glm::vec3 forward   = camera->Front;
    glm::vec3 right     = camera->Right;
    glm::vec3 up        = camera->Up;

    float velocity = moveSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += forward * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= forward * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += right * velocity;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        pos += up * velocity;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        pos -= up * velocity;
}