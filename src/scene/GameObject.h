#pragma once

#include <string>
#include <memory>
#include "Transform.h"

class Model;

class GameObject {
public:
    GameObject(const std::string& name, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f);

    void setModel(std::shared_ptr<Model> model);
    void draw(unsigned int shaderProgram) const;
    void update();

    const std::string& getName() const;

    Transform& getTransform();

private:
    std::string m_name;
    std::shared_ptr<Model> m_model;
    Transform m_transform;
};