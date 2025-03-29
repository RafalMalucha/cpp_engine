#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <tuple>

GLFWwindow* createWindow(int width, int height, const char* title);

void closeWindow(GLFWwindow* window, const char* title);

GLFWwindow* initializeEngineWindow();

GLFWmonitor* getPrimaryMonitor();

std::tuple<int, int> calculateWindowResolution(GLFWmonitor* primary);

#endif // WINDOWMANAGER_H