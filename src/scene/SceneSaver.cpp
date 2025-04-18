// get scene
// get info about scene
// for element in scene get everything save to json

#include <json.hpp>
using json = nlohmann::json;

#include <iostream>
#include <fstream>
#include <iomanip> 
#include "Scene.h"
#include "Model.h"
#include "utils/Utils.h"

int SceneSaver(Scene& scene) {

    std::cout << "Saving" << std::endl;
    std::cout << scene.getName() << std::endl;

    json root;
    root["sceneName"] = scene.getName();

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

    const std::string filename = scene.getName() + ".json";

    std::ofstream out(filename, std::ios::trunc);
    if (!out)
    {
        std::cerr << "SceneSaver ‑‑ cannot open " << filename << " for writing!\n";
        return 0;
    }

    out << std::setw(4) << root;
    std::cout << "Scene successfully saved to " << filename << '\n';
    return 1;
}