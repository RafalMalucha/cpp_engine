#include "GameObject.h"
#include "Model.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

GameObject::GameObject(const std::string& name, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ)
    : m_name(name), m_model(nullptr) {
    m_transform.position = { posX, posY, posZ };
    m_transform.rotation = glm::radians(glm::vec3(rotX, rotY, rotZ));
    m_transform.scale = { scaleX, scaleY, scaleZ };
}

void GameObject::setModel(std::shared_ptr<Model> model) {
    m_model = model;
}

void GameObject::savePreviousTransform() {
    m_prevTransform = m_transform;
}

void GameObject::draw(unsigned int shaderProgram) const {
    if (m_model) {
        glm::mat4 modelMatrix = m_transform.getMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        m_model->draw(shaderProgram);
    }
}

void GameObject::drawInterpolated(unsigned int shaderProgram, float alpha) const {
    Transform transform;

    transform.position = glm::mix(m_prevTransform.position,
                          m_transform.position,
                          alpha);
    transform.rotation = glm::mix(m_prevTransform.rotation,
                          m_transform.rotation,
                          alpha);
    transform.scale    = glm::mix(m_prevTransform.scale,
                          m_transform.scale,
                          alpha);

    glm::mat4 matrix = transform.getMatrix();
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "model"),
        1, GL_FALSE,
        glm::value_ptr(matrix)
    );

    if (m_model) m_model->draw(shaderProgram);
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

std::shared_ptr<Model> GameObject::getModel() {
    return m_model;
}

std::shared_ptr<const Model> GameObject::getModel() const {
    return m_model;
}

bool GameObject::getUsePhysics() {
    return m_usePhysics;
}

void GameObject::setUsePhysics(bool usePhysics) {
    m_usePhysics = usePhysics;
    std::cout << "set use physics to " << usePhysics << std::endl;
}

float GameObject::getMass() {
    return m_mass;
}

void GameObject::setMass(float mass) {
    m_mass = mass;
    std::cout << "set mass to " << mass << std::endl;
}