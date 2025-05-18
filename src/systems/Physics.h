#pragma once
#include <vector>
#include "PhysicsBody.h"

class Physics {
    public:
        void addBody(PhysicsBody* body);
        void simulate(float dt);

    private:
        void handleCollisions();
        std::vector<PhysicsBody*> bodies;
};