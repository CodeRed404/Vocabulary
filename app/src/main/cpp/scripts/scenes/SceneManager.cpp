//
// Created by codered404 on 01.11.26.
//

#include "SceneManager.h"
#include "Scene.h"
#include "Opening.h"

std::stack<Scene*>* SceneManager::scenes = nullptr;
Opening* SceneManager::opening = nullptr;


SceneManager::~SceneManager() {
    for (int i = 0; i < scenes->size(); i++) {
        delete scenes->top();
        scenes->pop();
    }

    delete scenes;
}

void SceneManager::Init() {
    scenes = new std::stack<Scene*>();
    opening = nullptr;

    //StartOpening(); // Opening animation
}

void SceneManager::Update(const float& delta) {
    if (scenes->empty())
        return;

    if (!opening) {
        if (scenes) {
            scenes->top()->Update(delta);
        }
    } else {
        opening->Update(delta);
        if (opening->Finish()) {
            delete opening;
            opening = nullptr;
        }
    }
}
void SceneManager::Draw() {
    if (scenes->empty())
        return;
    scenes->top()->Draw();

    if (opening) {
        opening->Draw();
    }
}

void SceneManager::AddScene(Scene* scene) {
    if (scene)
        scenes->push(scene);
}
void SceneManager::PopScene() {
    delete scenes->top();
    scenes->pop();
}

bool SceneManager::Empty() {
    return scenes->empty();
}

void SceneManager::StartOpening() {
    if (opening)
        return;

    opening = new Opening();
}
