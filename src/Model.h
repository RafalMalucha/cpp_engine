#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "Mesh.h"
#include "tiny_gltf.h"

class Model {
public:
    Model(const std::string& path);
    void draw() const;

private:
    std::vector<Mesh> meshes;
    void loadModel(const std::string& path);
    void processNode(const tinygltf::Model& model, const tinygltf::Node& node);
    Mesh processMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh);
};

#endif // MODEL_H
