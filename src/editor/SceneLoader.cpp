#include <fstream>
#include <iostream>
#include <json.hpp>
#include "scene/Scene.h"
#include "scene/Model.h"
using json = nlohmann::json;

Scene sceneLoader(const std::string& path) {

    std::ifstream f(path);
    json data = json::parse(f);

    Scene loadedScene(data["sceneName"]);

    loadedScene.setSkybox({
        data["skybox"][0],
        data["skybox"][1],
        data["skybox"][2],
        data["skybox"][3],
        data["skybox"][4],
        data["skybox"][5]
    });

    const json& objects = data.at("objects");

    for (const auto& object : objects) {
        loadedScene.createGameObject(object["name"],
            object["position"][0], object["position"][1], object["position"][2],
            object["rotation"][0], object["rotation"][1], object["rotation"][2],
            object["scale"][0], object["scale"][1], object["scale"][2])->setModel(std::make_shared<Model>(object["model"]));

        loadedScene.findByName(object["name"])->setUsePhysics(object["usePhysics"]);
        if (loadedScene.findByName(object["name"])->getUsePhysics()) {
            loadedScene.findByName(object["name"])->setMass(object["mass"]);
        }
    }

    return loadedScene;
}