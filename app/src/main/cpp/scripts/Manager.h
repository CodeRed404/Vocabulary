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
        static void DrawBackground();
        static void Draw();

        static void Warning(std::string warning, float time, Color color);
    private:
        Manager() {}

        static void UpdateWarning(const float& delta);
        static void DrawWarning();

        static std::string warning_text;
        static float warning_timer;
        static Color warning_color;
        static float warning_text_fontSize;
        static float warning_text_spacing;
        static Vector2 warning_text_size;
        static Vector2 warning_size;
        static Vector2 warning_position;
        static bool warning_appeard;
        static uint8_t warning_alpha;
        static float warning_alpha_timer;
        static constexpr float WARNING_ALPHA_TIME = 2.0f / 255;
};


#endif //VOCABULARY_MANAGER_H
