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
        inline static bool exitProgram = false;         // in need of improvement
        inline static float pressedTimer = 0.0f;        // in need of improvement !
        inline static bool isLoading = true;

        static Color MakeColorDarker(const Color& color, const float& percentage) {
            int newR;
            int newG;
            int newB;

            newR = color.r - color.r * percentage;
            newG = color.g - color.g * percentage;
            newB = color.b - color.b * percentage;

            newR = (newR > 255) ? 255 : ((newR < 0) ? 0 : newR);
            newG = (newG > 255) ? 255 : ((newG < 0) ? 0 : newG);
            newB = (newB > 255) ? 255 : ((newB < 0) ? 0 : newB);

            Color newCol = color;
            newCol.r = newR;
            newCol.g = newG;
            newCol.b = newB;

            return newCol;
        }
        static Color MakeColorLighter(const Color& color, const float& percentage) {
            int newR;
            int newG;
            int newB;

            newR = color.r + color.r * percentage;
            newG = color.g + color.g * percentage;
            newB = color.b + color.b * percentage;

            newR = (newR > 255) ? 255 : ((newR < 0) ? 0 : newR);
            newG = (newG > 255) ? 255 : ((newG < 0) ? 0 : newG);
            newB = (newB > 255) ? 255 : ((newB < 0) ? 0 : newB);

            Color newCol = color;
            newCol.r = newR;
            newCol.g = newG;
            newCol.b = newB;

            return newCol;
        }
    private:
        Global() {}
};

#endif //VOCABULARY_GLOBAL_H
