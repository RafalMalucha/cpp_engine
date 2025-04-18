#pragma once

#include <vector>
#include <string>
#include <memory>
#include "GameObject.h"
#include "Skybox.h"

class Scene {
public:

    Scene(const std::string& name);

    std::shared_ptr<GameObject> createGameObject(const std::string& name, 
        float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, 
        float rotX = 0.0f, float rotY = 0.0f, float rotZ = 0.0f, 
        float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f);

    void removeGameObject(const std::string& name);

    std::shared_ptr<GameObject> findByName(const std::string& name);
    std::vector<std::shared_ptr<GameObject>> getAllGameObjects();

    void setSkybox(const std::vector<std::string>& faces);

    Skybox getSkybox() const;

    void update();
    void draw(unsigned int shaderProgram);

    const std::string& getName() const;

    void clear();

private:
    std::string sceneName;
    Skybox m_skybox;
    std::vector<std::shared_ptr<GameObject>> m_objects;
};