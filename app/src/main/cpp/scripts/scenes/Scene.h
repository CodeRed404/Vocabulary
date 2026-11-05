//
// Created by codered404 on 01.11.26.
//

#ifndef VOCABULARY_SCENE_H
#define VOCABULARY_SCENE_H

#include "raylib.h"
#include "../ui/Button.h"
#include "../ui/Text.h"

class Scene {
    public:
        virtual ~Scene() = default;

        virtual void Update(const float& delta);
        virtual void Draw();
    protected:
        Scene();
};

#endif //VOCABULARY_SCENE_H
