#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include "scene/GameObject.h"
#include "scene/Model.h"

void gameObjectManager(std::shared_ptr<GameObject> gameObject, bool show_object_manager) {

    Transform& tr = gameObject->getTransform();

    glm::vec3 pos = tr.position;
    glm::vec3 rotDeg = glm::degrees(tr.rotation);
    glm::vec3 scale = tr.scale;

    ImGui::Begin("Game Object Manager", &show_object_manager);
    ImGui::Text(gameObject->getName().c_str());
    ImGui::Text("---------------------------------");
    ImGui::Text("Model");
    ImGui::Text(gameObject->getModel()->getMeshPath().c_str());
    ImGui::Text("---------------------------------");
    ImGui::Text("Use Physics");
    if (gameObject->getUsePhysics()) {
        ImGui::Text("true");
    } else {
        ImGui::Text("false");
    }
    ImGui::Text("------------------");
    ImGui::Text("Mass: %.2f", (double)gameObject->getMass());
    ImGui::Text("---------------------------------");
    ImGui::Text("Transform");
    ImGui::Text("------------------");
    ImGui::Text("Position");
    if (ImGui::InputFloat3("Position", &pos.x)) {
        tr.position = pos;         
    }
    ImGui::Text("------------------");
    ImGui::Text("Rotation");
    if (ImGui::InputFloat3("Rotation", &rotDeg.x)) {
        tr.rotation = glm::radians(rotDeg);         
    }
    ImGui::Text("------------------");
    ImGui::Text("Scale");
    if (ImGui::InputFloat3("Scale", &scale.x)) {
        tr.scale = scale;         
    }

    ImGui::End();
}