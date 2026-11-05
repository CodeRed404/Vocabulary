//
// Created by codered404 on 01.11.26.
//

#ifndef VOCABULARY_SCENEMANAGER_H
#define VOCABULARY_SCENEMANAGER_H

#include "stack"

class Scene;
class Opening;

class SceneManager {
    public:
        ~SceneManager();

        static void Init();
        static void Update(const float& delta);
        static void Draw();

        static void AddScene(Scene* scene);
        static void PopScene();
        static bool Empty();
        static void StartOpening();
    private:
        static std::stack<Scene*>* scenes;

        static Opening* opening;
};


#endif //VOCABULARY_SCENEMANAGER_H
