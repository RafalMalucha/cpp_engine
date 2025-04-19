#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include "GameObject.h"

void gameObjectManager(std::shared_ptr<GameObject> gameObject, bool show_object_manager) {
    ImGui::Begin("Game Object Manager", &show_object_manager);
    ImGui::Text(gameObject->getName().c_str());
    ImGui::End();
}