// get scene
// get info about scene
// for element in scene get everything save to json

#include <json.hpp>
using json = nlohmann::json;

#include <iostream>
#include <fstream>
#include <iomanip> 
#include "scene/Scene.h"
#include "scene/Model.h"
#include "utils/Utils.h"

int SceneSaver(Scene& scene) {

    std::cout << "Saving" << std::endl;
    std::cout << scene.getName() << std::endl;

    json root;
    root["sceneName"] = scene.getName();

    json skyboxFaces = json::array();

    for (int i = 0; i < 6; i++) {
        skyboxFaces.push_back(scene.getSkybox().getFaces()[i]);
    }

    root["skybox"] = skyboxFaces;

    json allObjectsArray = json::array();
    //std::cout << scene.getAllGameObjects << std::endl;
    for (const auto& obj : scene.getAllGameObjects()) {
        
        json objectArray;

        objectArray["name"] = obj->getName();
        objectArray["model"] = obj->getModel() ? obj->getModel()->getMeshPath() : "";
        objectArray["usePhysics"] = obj->getUsePhysics();

        if (obj->getUsePhysics()) {
            objectArray["mass"] = obj->getMass();
        }

        json positionArray = json::array();

        positionArray.push_back(obj->getTransform().position[0]);
        positionArray.push_back(obj->getTransform().position[1]);
        positionArray.push_back(obj->getTransform().position[2]);

        objectArray["position"] = positionArray;

        json rotationArray = json::array();

        rotationArray.push_back(glm::degrees(obj->getTransform().rotation[0]));
        rotationArray.push_back(glm::degrees(obj->getTransform().rotation[1]));
        rotationArray.push_back(glm::degrees(obj->getTransform().rotation[2]));

        objectArray["rotation"] = rotationArray;

        json scaleArray = json::array();

        scaleArray.push_back(obj->getTransform().scale[0]);
        scaleArray.push_back(obj->getTransform().scale[1]);
        scaleArray.push_back(obj->getTransform().scale[2]);

        objectArray["scale"] = scaleArray;

        allObjectsArray.push_back(objectArray);
    }

    root ["objects"] = allObjectsArray;

    const std::string filename = "assets/scenes/" + scene.getName() + ".json";

    std::ofstream out(filename, std::ios::trunc);
    if (!out)
    {
        std::cerr << "SceneSaver - cannot open " << filename << " for writing!\n";
        return 0;
    }

    out << std::setw(4) << root;
    std::cout << "Scene successfully saved to " << filename << '\n';
    return 1;
}