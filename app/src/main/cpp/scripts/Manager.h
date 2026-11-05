//
// Created by codered404 on 01.11.26.
//

#ifndef VOCABULARY_MANAGER_H
#define VOCABULARY_MANAGER_H

#include "raylib.h"
#include "AssetManager.h"
#include "scenes/SceneManager.h"
#include "scenes/Menu.h"
#include "string"

class Manager {
    public:
        static void Update(const float& delta);
        static void Draw();
    private:
        Manager() {}
};


#endif //VOCABULARY_MANAGER_H
