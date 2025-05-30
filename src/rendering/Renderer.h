#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"
#include "scene/Skybox.h"
#include "scene/Model.h" 
#include "scene/Scene.h" 
#include <GLFW/glfw3.h>

void renderFrame(GLFWwindow* window, unsigned int shaderProgram, Scene& scene, Camera camera, float alpha);

#endif // RENDERER_H
