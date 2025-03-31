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

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
};

#endif // CAMERA_H
