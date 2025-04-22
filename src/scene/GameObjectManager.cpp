#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include "GameObject.h"
#include "Model.h"

void gameObjectManager(std::shared_ptr<GameObject> gameObject, bool show_object_manager) {
    ImGui::Begin("Game Object Manager", &show_object_manager);
    ImGui::Text(gameObject->getName().c_str());
    ImGui::Text("---------------------------------");
    ImGui::Text("Model");
    ImGui::Text(gameObject->getModel()->getMeshPath().c_str());
    ImGui::Text("---------------------------------");
    ImGui::Text("Transform");
    ImGui::Text("------------------");
    ImGui::Text("Position");
    ImGui::Text("x = %.2f", gameObject->getTransform().position[0]);
    ImGui::Text("y = %.2f", gameObject->getTransform().position[1]);
    ImGui::Text("z = %.2f", gameObject->getTransform().position[2]);
    ImGui::Text("------------------");
    ImGui::Text("Rotation");
    ImGui::Text("x = %.2f", glm::degrees(gameObject->getTransform().rotation[0]));
    ImGui::Text("y = %.2f", glm::degrees(gameObject->getTransform().rotation[1]));
    ImGui::Text("z = %.2f", glm::degrees(gameObject->getTransform().rotation[2]));
    ImGui::Text("------------------");
    ImGui::Text("Scale");
    ImGui::Text("x = %.2f", gameObject->getTransform().scale[0]);
    ImGui::Text("y = %.2f", gameObject->getTransform().scale[1]);
    ImGui::Text("z = %.2f", gameObject->getTransform().scale[2]);

    ImGui::End();
}