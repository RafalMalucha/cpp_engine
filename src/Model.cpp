#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"
#include "stb_image.h"

Model::Model(const std::string& path) {
    loadModel(path);
}

void Model::draw(unsigned int shaderProgram) const {
    for (const auto& mesh : meshes) {
        mesh.draw(shaderProgram);
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
        for (const auto& primitive : mesh.primitives) {
            meshes.push_back(processPrimitive(model, primitive));
        }
    }

    for (int childIndex : node.children) {
        processNode(model, model.nodes[childIndex]);
    }
}

Mesh Model::processPrimitive(const tinygltf::Model& model, const tinygltf::Primitive& primitive) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    glm::vec3 baseColor = glm::vec3(1.0f);
    unsigned int textureID = 0;
    bool hasTexture = false;

    // === VERTEX ATTRIBUTES ===
    const auto& posAccessor = model.accessors[primitive.attributes.at("POSITION")];
    const auto& posView = model.bufferViews[posAccessor.bufferView];
    const auto& posBuffer = model.buffers[posView.buffer];
    const float* posData = reinterpret_cast<const float*>(&posBuffer.data[posView.byteOffset + posAccessor.byteOffset]);

    const float* normData = nullptr;
    if (primitive.attributes.count("NORMAL")) {
        const auto& accessor = model.accessors[primitive.attributes.at("NORMAL")];
        const auto& view = model.bufferViews[accessor.bufferView];
        const auto& buffer = model.buffers[view.buffer];
        normData = reinterpret_cast<const float*>(&buffer.data[view.byteOffset + accessor.byteOffset]);
    }

    const float* texData = nullptr;
    if (primitive.attributes.count("TEXCOORD_0")) {
        const auto& accessor = model.accessors[primitive.attributes.at("TEXCOORD_0")];
        const auto& view = model.bufferViews[accessor.bufferView];
        const auto& buffer = model.buffers[view.buffer];
        texData = reinterpret_cast<const float*>(&buffer.data[view.byteOffset + accessor.byteOffset]);
    }

    size_t vertexCount = posAccessor.count;
    for (size_t i = 0; i < vertexCount; ++i) {
        Vertex v;
        v.Position = glm::vec3(posData[i * 3 + 0], posData[i * 3 + 1], posData[i * 3 + 2]);
        v.Normal = normData ? glm::vec3(normData[i * 3 + 0], normData[i * 3 + 1], normData[i * 3 + 2]) : glm::vec3(0.0f);
        v.TexCoords = texData ? glm::vec2(texData[i * 2 + 0], texData[i * 2 + 1]) : glm::vec2(0.0f);
        vertices.push_back(v);
    }

    // === INDICES ===
    const auto& idxAccessor = model.accessors[primitive.indices];
    const auto& idxView = model.bufferViews[idxAccessor.bufferView];
    const auto& idxBuffer = model.buffers[idxView.buffer];
    const void* idxData = &idxBuffer.data[idxView.byteOffset + idxAccessor.byteOffset];

    for (size_t i = 0; i < idxAccessor.count; ++i) {
        unsigned int index = 0;
        switch (idxAccessor.componentType) {
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                index = reinterpret_cast<const uint16_t*>(idxData)[i]; break;
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
                index = reinterpret_cast<const uint32_t*>(idxData)[i]; break;
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
                index = reinterpret_cast<const uint8_t*>(idxData)[i]; break;
        }
        indices.push_back(index);
    }

    // === MATERIAL ===
    if (primitive.material >= 0 && primitive.material < model.materials.size()) {
        const auto& mat = model.materials[primitive.material];

        // baseColorFactor
        if (mat.values.contains("baseColorFactor")) {
            const auto& colorVec = mat.values.at("baseColorFactor").ColorFactor();
            baseColor = glm::vec3(colorVec[0], colorVec[1], colorVec[2]);
        }

        // baseColorTexture
        if (mat.values.contains("baseColorTexture")) {
            int texIndex = mat.values.at("baseColorTexture").TextureIndex();
            if (texIndex >= 0 && texIndex < model.textures.size()) {
                const auto& texture = model.textures[texIndex];
                int imgIndex = texture.source;
                if (imgIndex >= 0 && imgIndex < model.images.size()) {
                    const auto& img = model.images[imgIndex];

                    glGenTextures(1, &textureID);
                    glBindTexture(GL_TEXTURE_2D, textureID);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                    GLenum format = GL_RGBA;
                    if (img.component == 3) format = GL_RGB;
                    else if (img.component == 1) format = GL_RED;

                    glTexImage2D(GL_TEXTURE_2D, 0, format, img.width, img.height, 0, format, GL_UNSIGNED_BYTE, img.image.data());
                    glGenerateMipmap(GL_TEXTURE_2D);
                    hasTexture = true;
                }
            }
        }
    }

    return Mesh(vertices, indices, baseColor, textureID, hasTexture);
}