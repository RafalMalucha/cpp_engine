#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "Mesh.h"
#include "tiny_gltf.h"

class Model {
public:
    Model(const std::string& path);
    void draw(unsigned int shaderProgram) const;
    std::string getMeshPath();

private:
    std::string meshPath;
    std::vector<Mesh> meshes;
    void loadModel(const std::string& path);
    void processNode(const tinygltf::Model& model, const tinygltf::Node& node);
    Mesh processPrimitive(const tinygltf::Model& model, const tinygltf::Primitive& primitive);
};

#endif // MODEL_H
