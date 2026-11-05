//
// Created by codered404 on 01.11.26.
//ss

#ifndef VOCABULARY_ASSETMANAGER_H
#define VOCABULARY_ASSETMANAGER_H

#include "raylib.h"
#include "string"

class AssetManager {
    public:
        enum FONT {
            FONT_HEADER,
            FONT_DEFAULT
        };

        enum SOUND {
            SOUND_BUTTON_HOVER,
            SOUND_BUTTON_PRESS,
            SOUND_OPENING_START,
            SOUND_OPENING_END
        };

        static void LoadAssets();
        static void UnloadAssets();

        static Font *GetFont(FONT font);
        static Sound *GetSound(SOUND sound);
    private:
        // Paths {
        // Fonts
        static std::string path_font_header;
        static std::string path_font_default;

        // Audio
        // Sounds
        // Buttons
        static std::string path_sound_button_hover;
        static std::string path_sound_button_click;
        // Opening
        static std::string path_sound_opening_start;
        static std::string path_sound_opening_end;
        // }

        // Fonts
        static Font font_header;
        static Font font_default;

        // Audio
        // Sounds
        // Buttons
        static Sound sound_button_hover;
        static Sound sound_button_click;
        // Opening
        static Sound sound_opening_start;        // in need of improvement => unload if opening scene get deleted
        static Sound sound_opening_end;          // in need of improvement => unload if opening scene get deleted
};


#endif //VOCABULARY_ASSETMANAGER_H
