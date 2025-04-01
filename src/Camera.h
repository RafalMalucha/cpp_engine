#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    Camera(); // default constructor
    glm::mat4 getViewMatrix() const;
    void handleInput(GLFWwindow* window);
    void lockMouse(GLFWwindow* window);
    glm::vec3 Position;

private:
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    bool isMouseLocked = true;
    bool firstMouse = true;
    double lastX = 0.0;
    double lastY = 0.0;
    double savedX = 0.0;
    double savedY = 0.0;

    float Yaw;
    float Pitch;
    float Sensitivity;

    void updateVectors();
};

#endif // CAMERA_H
