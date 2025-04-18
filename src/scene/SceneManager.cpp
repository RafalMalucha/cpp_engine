#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Scene.h"
#include "Skybox.h"
#include "SceneSaver.h"
#include "SceneLoader.h"

void sceneManager(Scene& scene) {
    ImGui::Begin("Scene Manager");
    if (ImGui::Button("Load test scene")) {
        scene = sceneLoader("assets/scenes/testScene.json");
    }
    if (ImGui::Button("Load empty scene")) {
        scene = sceneLoader("assets/scenes/emptyScene.json");
    }
    if (ImGui::Button("Save")) {
        SceneSaver(scene);
    }
    ImGui::End();
}