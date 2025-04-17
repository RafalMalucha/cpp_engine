#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::string currentDateTime();

void launchNewTerminalOnLinux();

void closeTerminalOnLinux();

float calculateFPS();

void printMatrix(const glm::mat4& matrix);

#endif // UTILS_H