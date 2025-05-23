#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "rendering/Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

void main_window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void char_callback(GLFWwindow* window, unsigned int codepoint);

extern std::vector<std::string> eventLog;

#endif // INPUTHANDLER_H
