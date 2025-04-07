#pragma once

#include <vector>
#include <string>
#include <memory>
#include "GameObject.h"

class Scene {
public:
    std::shared_ptr<GameObject> createGameObject(const std::string& name);
    void removeGameObject(const std::string& name);

    std::shared_ptr<GameObject> findByName(const std::string& name);
    std::vector<std::shared_ptr<GameObject>> getAllGameObjects();

    void update();
    void draw(unsigned int shaderProgram);

    void clear();

private:
    std::vector<std::shared_ptr<GameObject>> m_objects;
};