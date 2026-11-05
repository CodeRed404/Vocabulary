//
// Created by codered404 on 02.11.26.
//

#include "Opening.h"

Opening::Opening() {
    finish = false;

    opening_speed = 0.01f;
    percent_open = 0.0f;

    timer_delay = 0.75f;

    opening_start_sound_played = false;
    opening_end_sound_played = false;

    color = BLACK;
}

void Opening::Update(const float &delta) {
    if (!opening_start_sound_played) {
        PlaySound(*AssetManager::GetSound(AssetManager::SOUND_OPENING_START));
        opening_start_sound_played = true;
    }

    if (percent_open < 0.05f) {
        percent_open += delta * opening_speed;
        opening_speed *= 1.1f;
    } else if (percent_open < 1.0f){
        if (timer_delay <= 0.0f) {
            if (IsSoundPlaying(*AssetManager::GetSound(AssetManager::SOUND_OPENING_START))) {
                StopSound(*AssetManager::GetSound(AssetManager::SOUND_OPENING_START));
            }

            if (!opening_end_sound_played) {
                PlaySound(*AssetManager::GetSound(AssetManager::SOUND::SOUND_OPENING_END));
                opening_end_sound_played = true;
                opening_speed *= 1.5;
            }

            percent_open += delta * opening_speed;
            opening_speed += delta * opening_speed;
            opening_speed *= 1.15;
        } else {
            timer_delay -= delta;
        }
    }

    if (percent_open >= 1.0f) {
        finish = true;
    }
}

void Opening::Draw() {
    DrawRectangleV({0, 0}, {(float)GetScreenWidth(), 0.5f * (float)GetScreenHeight() * (1.0f - percent_open)}, color);
    DrawRectangleV({0, 0.5f * (float)GetScreenHeight() + (0.5f * (float)GetScreenHeight() * percent_open)}, {(float)GetScreenWidth(), 0.5f * (float)GetScreenHeight() * (1.0f - percent_open)}, color);
}

bool Opening::Finish() {
    return finish;
}