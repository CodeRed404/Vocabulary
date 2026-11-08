//
// Created by codered404 on 01.11.26.
//

#include "AssetManager.h"


std::string AssetManager::path_font_header = "fonts/mango/Mango-Fill.ttf";
std::string AssetManager::path_font_default_regular = "fonts/default/default_regular.ttf";
std::string AssetManager::path_font_default_bold = "fonts/default/default_bold.ttf";
std::string AssetManager::path_font_mango_fill = "fonts/mango/Mango-Fill.ttf";
std::string AssetManager::path_font_mango_rg = "fonts/mango/Mango-Rg.ttf";
std::string AssetManager::path_font_mango_scribble = "fonts/mango/Mango-Scribble.ttf";
std::string AssetManager::path_sound_button_hover = "audio/sounds/ui/button_hover.wav";
std::string AssetManager::path_sound_button_click = "audio/sounds/ui/button_click.wav";
std::string AssetManager::path_sound_opening_start = "audio/sounds/opening_start.wav";
std::string AssetManager::path_sound_opening_end = "audio/sounds/opening_end.wav";
std::string AssetManager::path_texture_robot_0 = "textures/robot/robot_0.png";
std::string AssetManager::path_texture_robot_1 = "textures/robot/robot_1.png";

Font AssetManager::font_header;
Font AssetManager::font_default_regular;
Font AssetManager::font_default_bold;
Font AssetManager::font_mango_fill;
Font AssetManager::font_mango_rg;
Font AssetManager::font_mango_scribble;
Sound AssetManager::sound_button_hover;
Sound AssetManager::sound_button_click;
Sound AssetManager::sound_opening_start;
Sound AssetManager::sound_opening_end;

Texture2D AssetManager::texture_robot_0;
Texture2D AssetManager::texture_robot_1;

void AssetManager::LoadAssets() {
    // Fonts
    int codepoints[256];
    int codepointCount = 0;
    // add standard ASCII characters (32 to 127)
    for (int i = 0; i < 96; i++) {
        codepoints[codepointCount++] = 32 + i;
    }
    // add german special characters
    codepoints[codepointCount++] = 196; // Ä
    codepoints[codepointCount++] = 214; // Ö
    codepoints[codepointCount++] = 220; // Ü
    codepoints[codepointCount++] = 228; // ä
    codepoints[codepointCount++] = 246; // ö
    codepoints[codepointCount++] = 252; // ü
    codepoints[codepointCount++] = 223; // ß

    font_header = LoadFontEx(path_font_header.c_str(), 256, codepoints, codepointCount);
    font_default_regular = LoadFontEx(path_font_default_regular.c_str(), 256, codepoints, codepointCount);
    font_default_bold = LoadFontEx(path_font_default_bold.c_str(), 256, codepoints, codepointCount);
    font_mango_fill = LoadFontEx(path_font_mango_fill.c_str(), 256, nullptr, 0);
    font_mango_rg = LoadFontEx(path_font_mango_rg.c_str(), 256, nullptr, 0);
    font_mango_scribble = LoadFontEx(path_font_mango_scribble.c_str(), 256, nullptr, 0);

    // Audio
    // Sounds
    // Buttons
    sound_button_hover = LoadSound(path_sound_button_hover.c_str());
    sound_button_click = LoadSound(path_sound_button_click.c_str());
    // Opening
    sound_opening_start = LoadSound(path_sound_opening_start.c_str());
    sound_opening_end = LoadSound(path_sound_opening_end.c_str());

    // Textures
    // Character
    texture_robot_0 = LoadTexture(path_texture_robot_0.c_str());
    texture_robot_1 = LoadTexture(path_texture_robot_1.c_str());
}

void AssetManager::UnloadAssets() {
    // Fonts
    UnloadFont(font_header);
    UnloadFont(font_default_regular);
    UnloadFont(font_default_bold);
    UnloadFont(font_mango_fill);
    UnloadFont(font_mango_rg);
    UnloadFont(font_mango_scribble);

    // Audio
    // Sounds
    // Buttons
    UnloadSound(sound_button_hover);
    UnloadSound(sound_button_click);
    // Opening
    UnloadSound(sound_opening_start);
    UnloadSound(sound_opening_end);

    // Textures
    // Robot
    UnloadTexture(texture_robot_0);
    UnloadTexture(texture_robot_1);
}


// Getters / Setters

Font *AssetManager::GetFont(FONT font) {
    switch (font) {
        case FONT::FONT_HEADER:
            return &font_header;
        case FONT::FONT_DEFAULT_REGULAR:
            return &font_default_regular;
        case FONT::FONT_DEFAULT_BOLD:
            return &font_default_bold;
        case FONT::FONT_BUTTON:
            return &font_header;
        case FONT::FONT_MANGO_FILL:
            return &font_mango_fill;
        case FONT::FONT_MANGO_RG:
            return &font_mango_rg;
        case FONT::FONT_MANGO_SCRIBBLE:
            return &font_mango_scribble;
    }
}

Sound *AssetManager::GetSound(SOUND sound) {
    switch (sound) {
        case SOUND::SOUND_BUTTON_HOVER:
            return &sound_button_hover;
        case SOUND::SOUND_BUTTON_PRESS:
            return &sound_button_click;
        case SOUND::SOUND_OPENING_START:
            return &sound_opening_start;
        case SOUND::SOUND_OPENING_END:
            return &sound_opening_end;
    }
}

Texture2D *AssetManager::GetTexture(TEXTURE texture) {
    switch (texture) {
        case TEXTURE::TEXTURE_ROBOT_0:
            return &texture_robot_0;
        case TEXTURE::TEXTURE_ROBOT_1:
            return &texture_robot_1;
    }
}