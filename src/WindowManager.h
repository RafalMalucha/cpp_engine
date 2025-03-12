#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <GLFW/glfw3.h>

GLFWwindow* createWindow(int width, int height, const char* title);

void closeWindow(GLFWwindow* window, const char* title);

#endif // WINDOWMANAGER_H