#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderLoader.h"
#include "OpenGLSetup.h"

void setupOpenGL(unsigned int& shaderProgram) {
    shaderProgram = loadShaders("assets/shaders/vertex_shader.glsl", "assets/shaders/fragment_shader.glsl");

    glUseProgram(shaderProgram);

    // Default directional light setup
    glUniform3f(glGetUniformLocation(shaderProgram, "lightDir"), 1.0f, 1.0f, 2.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f);
}