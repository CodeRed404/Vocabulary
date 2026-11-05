//
// Created by codered404 on 01.11.26.
//

#include "AssetManager.h"


std::string AssetManager::path_font_header = "fonts/Hoover/Fonts/Hoover-Variable.ttf";
std::string AssetManager::path_font_default = "fonts/Karma/Fonts/Karma-Variable.ttf";
std::string AssetManager::path_sound_button_hover = "audio/sounds/ui/button_hover.wav";
std::string AssetManager::path_sound_button_click = "audio/sounds/ui/button_click.wav";
std::string AssetManager::path_sound_opening_start = "audio/sounds/opening_start.wav";
std::string AssetManager::path_sound_opening_end = "audio/sounds/opening_end.wav";

Font AssetManager::font_header;
Font AssetManager::font_default;
Sound AssetManager::sound_button_hover;
Sound AssetManager::sound_button_click;
Sound AssetManager::sound_opening_start;
Sound AssetManager::sound_opening_end;

void AssetManager::LoadAssets() {
    // Fonts
    font_header = LoadFontEx(path_font_header.c_str(), 256, nullptr, 0);
    font_default = LoadFontEx(path_font_default.c_str(), 256, nullptr, 0);

    // Audio
    // Sounds
    // Buttons
    sound_button_hover = LoadSound(path_sound_button_hover.c_str());
    sound_button_click = LoadSound(path_sound_button_click.c_str());
    // Opening
    sound_opening_start = LoadSound(path_sound_opening_start.c_str());
    sound_opening_end = LoadSound(path_sound_opening_end.c_str());
}

void AssetManager::UnloadAssets() {
    // Fonts
    UnloadFont(font_header);
    UnloadFont(font_default);

    // Audio
    // Sounds
    // Buttons
    UnloadSound(sound_button_hover);
    UnloadSound(sound_button_click);
    // Opening
    UnloadSound(sound_opening_start);
    UnloadSound(sound_opening_end);
}


// Getters / Setters

Font *AssetManager::GetFont(FONT font) {
    switch (font) {
        case FONT::FONT_HEADER:
            return &font_header;
        case FONT::FONT_DEFAULT:
            return &font_default;
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