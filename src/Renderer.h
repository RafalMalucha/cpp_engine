#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"
#include "Skybox.h"
#include "Model.h" 
#include <GLFW/glfw3.h>

void renderFrame(GLFWwindow* window, unsigned int shaderProgram, Model& model, Camera camera, Skybox& skybox);

#endif // RENDERER_H
