#pragma once

#include <string>
#include <memory>

class Model;

class GameObject {
public:
    GameObject(const std::string& name);

    void setModel(std::shared_ptr<Model> model);
    void draw(unsigned int shaderProgram) const;
    void update();

    const std::string& getName() const;

private:
    std::string m_name;
    std::shared_ptr<Model> m_model;
};