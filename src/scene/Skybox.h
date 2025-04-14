#ifndef SKYBOX_H
#define SKYBOX_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Skybox {
public:
    Skybox();
    void init(const std::vector<std::string>& faces);
    void render(const glm::mat4& view, const glm::mat4& projection);
private:
    unsigned int cubemapTexture;
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int shaderProgram;

    unsigned int loadCubemap(const std::vector<std::string>& faces);
};

#endif // SKYBOX_H