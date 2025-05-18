// PhysicsBody.h
#pragma once
#include <glm/glm.hpp>
#include "scene/Transform.h"

struct PhysicsBody {
    Transform* transform;        // pointer to the GameObject’s transform
    float mass;                  // > 0
    glm::vec3 velocity{0.0f};
    glm::vec3 forces{0.0f};
    float restitution{0.5f};     // bounciness [0..1]

    PhysicsBody(Transform* t, float m)
      : transform(t), mass(m) {}

    void applyForce(const glm::vec3& f) {
      forces += f;
    }

    void integrate(float dt) {
      // a = F / m
      glm::vec3 accel = forces / mass;
      // Euler integration
      velocity += accel * dt;
      transform->position += velocity * dt;
      // reset forces
      forces = glm::vec3(0.0f);
    }
};
