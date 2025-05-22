#pragma once
#include "rendering/Camera.h"
#include <GLFW/glfw3.h>

class EditorAgent {
    public:
        EditorAgent(Camera* camera);

        void handleInput(GLFWwindow* window, float deltaTime);

        void setMoveSpeed(float speed);

    private:
        Camera* camera;
        float moveSpeed = 5.0f;
};