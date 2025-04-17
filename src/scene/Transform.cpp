#include "Transform.h"

Transform::Transform()
    : position(0.0f), rotation(0.0f), scale(1.0f) {}

glm::mat4 Transform::getMatrix() const {
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, position);

    matrix = glm::rotate(matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    matrix = glm::scale(matrix, scale);
    
    return matrix;
}