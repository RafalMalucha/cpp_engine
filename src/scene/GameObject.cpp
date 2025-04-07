#include "GameObject.h"
#include "Model.h"

#include <iostream>

GameObject::GameObject(const std::string& name)
    : m_name(name), m_model(nullptr) {}

void GameObject::setModel(std::shared_ptr<Model> model) {
    m_model = model;
}

void GameObject::draw(unsigned int shaderProgram) const {
    if (m_model) {
        m_model->draw(shaderProgram);
    }
}

const std::string& GameObject::getName() const {
    return m_name;
}

void GameObject::update() {
    std::cout << "update placeholder" << std::endl;
}
