#include "GameObject.h"
#include "Model.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

GameObject::GameObject(const std::string& name, float posX, float posY, float posZ)
    : m_name(name), m_model(nullptr) {
    m_transform.position = { posX, posY, posZ };
}

void GameObject::setModel(std::shared_ptr<Model> model) {
    m_model = model;
}

void GameObject::draw(unsigned int shaderProgram) const {
    if (m_model) {
        glm::mat4 modelMatrix = m_transform.getMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        m_model->draw(shaderProgram);
    }
}

const std::string& GameObject::getName() const {
    return m_name;
}

void GameObject::update() {
    std::cout << "update placeholder " << getName() << std::endl;
}

Transform& GameObject::getTransform() {
    return m_transform;
}
