//
// Created by codered404 on 01.11.26.
//

#include "Manager.h"
#include "scenes/SceneManager.h"
#include "scenes/Menu.h"

void Manager::Update(const float& delta) {
    if (SceneManager::Empty()) {
        SceneManager::AddScene(new Menu());
    }
    SceneManager::Update(delta);
}

void Manager::Draw() {
    SceneManager::Draw();
}