#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <iostream>
#include <string>
#include "scene/Scene.h"
#include "scene/GameObject.h"

void gameObjectManager(std::shared_ptr<GameObject> gameObject, bool show_object_manager);

#endif GAMEOBJECTMANAGER_H