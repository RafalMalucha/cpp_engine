#include "Physics.h"
#include <iostream>
#include <glm/glm.hpp>

void Physics::addBody(PhysicsBody* body){
    bodies.push_back(body);
}

void Physics::simulate(float dt) {
    //gravity
    for (auto body : bodies) {
        body->applyForce(glm::vec3(0.0f, -9.81f * body->mass, 0.0f));
        body->integrate(dt);
    }

    //collisions
    handleCollisions();
}

void Physics::handleCollisions() {
    for (auto body : bodies) {
        std::cout << "collision handler placeholder" << std::endl;
        std::cout << body->transform->position[0] << body->transform->position[1] << body->transform->position[2] << std::endl;
    }
}