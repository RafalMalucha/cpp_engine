#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"
#include <GLFW/glfw3.h>

void renderFrame(GLFWwindow* window, unsigned int shaderProgram, unsigned int VAO, Camera camera);

#endif // RENDERER_H
