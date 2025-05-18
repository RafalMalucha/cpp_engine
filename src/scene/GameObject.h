#pragma once

#include <string>
#include <memory>
#include "Transform.h"

class Model;

class GameObject {
public:
    GameObject(const std::string& name, 
        float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, 
        float rotX = 0.0f, float rotY = 0.0f, float rotZ = 0.0f, 
        float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f);

    void setModel(std::shared_ptr<Model> model);
    std::shared_ptr<Model>       getModel();        // non‑const
    std::shared_ptr<const Model> getModel() const;  // const‑qualified

    void draw(unsigned int shaderProgram) const;
    void update();

    const std::string& getName() const;

    Transform& getTransform();
    bool getUsePhysics();
    void setUsePhysics(bool usePhysics);

private:
    std::string m_name;
    std::shared_ptr<Model> m_model;
    Transform m_transform;
    bool m_usePhysics;
};