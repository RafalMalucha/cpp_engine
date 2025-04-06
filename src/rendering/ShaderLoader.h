#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <string>

std::string readShaderFile(const char* filePath);

unsigned int loadShaders(const std::string& vertexPath, const std::string& fragmentPath);

#endif // SHADERLOADER_H