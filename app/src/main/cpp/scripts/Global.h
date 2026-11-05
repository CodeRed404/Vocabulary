//
// Created by codered404 on 01.11.26.
//

#ifndef VOCABULARY_GLOBAL_H
#define VOCABULARY_GLOBAL_H

#include "raylib.h"
#include "AssetManager.h"
#include "string"

class Global {
    public:
        static void LoadTemplates();

        inline static bool exitProgram = false;         // in need of improvement
        inline static float pressedTimer = 0.0f;        // in need of improvement !
        inline static std::string text = "1";
};

#endif //VOCABULARY_GLOBAL_H
