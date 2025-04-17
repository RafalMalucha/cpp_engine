// get scene
// get info about scene
// for element in scene get everything save to json

#include <iostream>
#include "Scene.h"
#include "Model.h"
#include "utils/Utils.h"

void SceneSaver(Scene& scene) {
    std::cout << "dupa" << std::endl;
    //std::cout << scene.getAllGameObjects << std::endl;
    for (const auto& obj : scene.getAllGameObjects()) {
        std::cout << obj->getName().c_str() << std::endl;

        std::cout << obj->getModel()->getMeshPath() << std::endl;

        std::cout << obj->getTransform().position[0] << "  ";
        std::cout << obj->getTransform().position[1] << "  ";
        std::cout << obj->getTransform().position[2] << std::endl;

        std::cout << glm::degrees(obj->getTransform().rotation[0]) << "  ",
        std::cout << glm::degrees(obj->getTransform().rotation[1]) << "  ",
        std::cout << glm::degrees(obj->getTransform().rotation[2]) << std::endl;

        std::cout << obj->getTransform().scale[0] << "  ";
        std::cout << obj->getTransform().scale[1] << "  ";
        std::cout << obj->getTransform().scale[2] << std::endl;
    }
}