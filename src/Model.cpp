#include "Model.h"
#include <iostream>

Model::Model(const std::string& path) {
    loadModel(path);
}

void Model::draw() const {
    for (const auto& mesh : meshes) {
        mesh.draw();
    }
}

void Model::loadModel(const std::string& path) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model gltfModel;
    std::string err, warn;

    bool success = path.ends_with(".glb")
        ? loader.LoadBinaryFromFile(&gltfModel, &err, &warn, path)
        : loader.LoadASCIIFromFile(&gltfModel, &err, &warn, path);

    if (!success) {
        std::cerr << "Failed to load glTF: " << err << std::endl;
        return;
    }

    for (const auto& node : gltfModel.nodes) {
        processNode(gltfModel, node);
    }
}

void Model::processNode(const tinygltf::Model& model, const tinygltf::Node& node) {
    if (node.mesh >= 0 && node.mesh < model.meshes.size()) {
        const auto& mesh = model.meshes[node.mesh];
        meshes.push_back(processMesh(model, mesh));
    }

    for (int childIndex : node.children) {
        processNode(model, model.nodes[childIndex]);
    }
}

Mesh Model::processMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (const auto& primitive : mesh.primitives) {
        const auto& posAccessor = model.accessors[primitive.attributes.find("POSITION")->second];
        const auto& posBufferView = model.bufferViews[posAccessor.bufferView];
        const auto& posBuffer = model.buffers[posBufferView.buffer];

        const float* posData = reinterpret_cast<const float*>(
            &posBuffer.data[posBufferView.byteOffset + posAccessor.byteOffset]
        );

        size_t vertexCount = posAccessor.count;

        const float* normData = nullptr;
        const float* texData = nullptr;

        if (primitive.attributes.count("NORMAL")) {
            const auto& accessor = model.accessors[primitive.attributes.at("NORMAL")];
            const auto& view = model.bufferViews[accessor.bufferView];
            const auto& buffer = model.buffers[view.buffer];
            normData = reinterpret_cast<const float*>(&buffer.data[view.byteOffset + accessor.byteOffset]);
        }

        if (primitive.attributes.count("TEXCOORD_0")) {
            const auto& accessor = model.accessors[primitive.attributes.at("TEXCOORD_0")];
            const auto& view = model.bufferViews[accessor.bufferView];
            const auto& buffer = model.buffers[view.buffer];
            texData = reinterpret_cast<const float*>(&buffer.data[view.byteOffset + accessor.byteOffset]);
        }

        for (size_t i = 0; i < vertexCount; ++i) {
            Vertex v;
            v.Position = glm::vec3(posData[i * 3 + 0], posData[i * 3 + 1], posData[i * 3 + 2]);
            v.Normal   = normData ? glm::vec3(normData[i * 3 + 0], normData[i * 3 + 1], normData[i * 3 + 2]) : glm::vec3(0.0f);
            v.TexCoords = texData ? glm::vec2(texData[i * 2 + 0], texData[i * 2 + 1]) : glm::vec2(0.0f);
            vertices.push_back(v);
        }

        // Indices
        const auto& idxAccessor = model.accessors[primitive.indices];
        const auto& idxView = model.bufferViews[idxAccessor.bufferView];
        const auto& idxBuffer = model.buffers[idxView.buffer];

        const void* idxData = &idxBuffer.data[idxView.byteOffset + idxAccessor.byteOffset];

        for (size_t i = 0; i < idxAccessor.count; ++i) {
            unsigned int index = 0;
            switch (idxAccessor.componentType) {
                case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                    index = reinterpret_cast<const uint16_t*>(idxData)[i];
                    break;
                case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
                    index = reinterpret_cast<const uint32_t*>(idxData)[i];
                    break;
                case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
                    index = reinterpret_cast<const uint8_t*>(idxData)[i];
                    break;
                default:
                    break;
            }
            indices.push_back(index);
        }
    }

    return Mesh(vertices, indices);
}
