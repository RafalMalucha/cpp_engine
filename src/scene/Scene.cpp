#include "Scene.h"
#include <iostream>
#include <algorithm>

Scene::Scene(const std::string& name) : sceneName(name) {}

const std::string& Scene::getName() const {
    return sceneName;
}

std::shared_ptr<GameObject> Scene::createGameObject(const std::string& name, 
    float posX, float posY, float posZ, 
    float rotX, float rotY, float rotZ, 
    float scaleX, float scaleY, float scaleZ) {
    auto obj = std::make_shared<GameObject>(name, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ);
    m_objects.push_back(obj);
    return obj;
}

void Scene::setSkybox(const std::vector<std::string>& faces) {
    m_skybox.init(faces);
}

Skybox Scene::getSkybox() const {
    return m_skybox;
}

void Scene::removeGameObject(const std::string& name) {
    m_objects.erase(
        std::remove_if(m_objects.begin(), m_objects.end(),
            [&name](const std::shared_ptr<GameObject>& obj) {
                return obj->getName() == name;
            }),
        m_objects.end()
    );
}

std::shared_ptr<GameObject> Scene::findByName(const std::string& name) {
    for (const auto& obj : m_objects) {
        if (obj->getName() == name)
            return obj;
    }
    return nullptr;
}

std::vector<std::shared_ptr<GameObject>> Scene::getAllGameObjects() {
    return m_objects;
}

void Scene::update() {
    for (const auto& obj : m_objects) {
        obj->update();
    }
}

void Scene::draw(unsigned int shaderProgram) {
    for (const auto& obj : m_objects) {
        obj->draw(shaderProgram);
    }
}

void Scene::clear() {
    m_objects.clear();
}
