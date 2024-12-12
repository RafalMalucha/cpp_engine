#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

void main_window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

extern std::vector<std::string> eventLog;

#endif // INPUTHANDLER_H