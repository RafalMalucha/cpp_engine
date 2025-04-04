#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 baseColor;

    Mesh(const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices,
        const glm::vec3& baseColor,
        unsigned int textureID,
        bool hasTexture);

    void draw(unsigned int shaderProgram) const;  

private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
    unsigned int textureID;
    bool hasTexture;
};

#endif // MESH_H
