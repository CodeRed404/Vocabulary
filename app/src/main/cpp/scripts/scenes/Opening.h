//
// Created by codered404 on 02.11.26.
//

#ifndef VOCABULARY_OPENING_H
#define VOCABULARY_OPENING_H

#include "raylib.h"
#include "../AssetManager.h"

class Opening{
    public:
        Opening();

        void Update(const float& delta);
        void Draw();

        bool Finish();
    private:
        bool finish;

        Color color;

        float opening_speed;
        float percent_open;

        float timer_delay;

        // Sounds
        bool opening_start_sound_played;
        bool opening_end_sound_played;
};


#endif //VOCABULARY_OPENING_H
