#include "Scene.h"
#include <algorithm>

std::shared_ptr<GameObject> Scene::createGameObject(const std::string& name) {
    auto obj = std::make_shared<GameObject>(name);
    m_objects.push_back(obj);
    return obj;
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


