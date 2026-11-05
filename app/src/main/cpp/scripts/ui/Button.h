//
// Created by codered404 on 02.11.26.
//

#ifndef VOCABULARY_BUTTON_H
#define VOCABULARY_BUTTON_H

#include "raylib.h"
#include "../Global.h"
#include "Text.h"

class Button  {
    public:
        struct ButtonColor {
            Color text_color_released;
            Color text_color_pressed;
            Color color_released_fill;
            Color color_pressed_fill;
            Color color_released_outline;
            Color color_pressed_outline;
        };
    public:
        Button(Text text, ButtonColor buttonColor, Vector2 size, Vector2 position);
        Button(Text text, ButtonColor buttonColor);
        Button();

        void Update(const float& delta);
        void Draw();

        void CenterX();
        void CenterY();

        bool IsPressed();
        void SetSize(Vector2 size);
        void SetPosition(Vector2 position);
        Vector2 GetSize();
        Vector2 GetPosition();

        inline static const ButtonColor DefaultButtonColor = ButtonColor{
                Color{53, 79, 82, 255},
                Color{82, 121, 111, 255},
                Color{82, 121, 111, 255},
                Color{47, 62, 70, 255},
                Color{47, 62, 70, 255},
                Color{47, 62, 70, 255}
        };
    private:
        Text text;
        Vector2 size;
        Vector2 position;
        Vector2 curr_position;
        ButtonColor buttonColor;

        Color curr_color_fill;
        Color curr_color_outline;

        bool inHitbox;
        bool inHitboxFromBeginning;
        bool isPressed;

        // sound
        bool isHoverSoundPlayed;

        void ValuesChanged();
        void SetPressedColors();
        void SetReleasedColors();
};


#endif //VOCABULARY_BUTTON_H
