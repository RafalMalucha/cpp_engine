#include <fstream>
#include <iostream>
#include <json.hpp>
#include "scene/Scene.h"
#include "utils/Utils.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "SceneManager.h"
#include "GameObjectManager.h"

static std::shared_ptr<GameObject> gSelectedObj; 
static bool show_object_manager = false;
bool isWireframe = false;
bool isModelOne = true;

void editor(Scene& currentScene) {
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        sceneManager(currentScene);

        ImGui::Begin("Editor");
        for (const auto& obj : currentScene.getAllGameObjects()) {
            if (ImGui::Button(obj->getName().c_str())) {

                gSelectedObj = obj; 
                show_object_manager = true; 

                std::cout << "-----------------" << std::endl;
                std::cout << "Transform.position" << std::endl;
                std::cout << obj->getTransform().position[0] << " x " << obj->getTransform().position[1] << " y " << obj->getTransform().position[2] << " z " <<  std::endl;

                std::cout << "-----------------" << std::endl;
                std::cout << "Transform.rotation" << std::endl;
                std::cout << obj->getTransform().rotation[0] << " x " << obj->getTransform().rotation[1] << " y " << obj->getTransform().rotation[2] << " z " <<  std::endl;

                std::cout << "-----------------" << std::endl;
                std::cout << "Transform.scale" << std::endl;
                std::cout << obj->getTransform().scale[0] << " x " << obj->getTransform().scale[1] << " y " << obj->getTransform().scale[2] << " z " <<  std::endl;

                std::cout << "-----------------" << std::endl;
                std::cout << "Transform.scale" << std::endl;
                printMatrix(obj->getTransform().getMatrix());

                std::cout << "-----------------------------------------------------------------------" << std::endl;
            }
        }
        if (ImGui::Button("Toggle Wireframe")) {
            isWireframe = !isWireframe;

            if (isWireframe) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
        ImGui::End();


        if (show_object_manager)                          
        {
            //ImGui::Begin("Gizmo controls", &show_object_manager); 
            gameObjectManager(gSelectedObj, &show_object_manager);
        }
}