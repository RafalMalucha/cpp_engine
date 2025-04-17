#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
    glm::vec3 position;
    glm::vec3 rotation; // Euler angles in radians
    glm::vec3 scale;

    Transform();

    glm::mat4 getMatrix() const;
};

#endif // TRANSFORM_H