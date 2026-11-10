//
// Created by codered404 on 02.11.26.
//

#include "Button.h"

Button::Button(Text text, ButtonColor buttonColor, Vector2 size, Vector2 position, float roundness, bool locked) {
    Button::text = text;
    Button::buttonColor = buttonColor;
    Button::size = size;
    Button::position = position;
    Button::curr_position = position;
    Button::roundness = roundness;
    Button::locked = locked;

    Button::mute = false;
    Button::onlyOutline = false;
    Button::mango = true;

    Button::alpha = 255;

    Button::text.SetColor(buttonColor.text_color_released);
    Button::curr_color_fill = buttonColor.color_released_fill;
    Button::curr_color_outline = buttonColor.color_released_outline;

    Button::inHitbox = false;
    Button::inHitboxFromBeginning = false;
    Button::isPressed = false;

    Button::isHoverSoundPlayed = false;

    ValuesChanged();
}

Button::Button(Text text, ButtonColor buttonColor, Vector2 size, Vector2 position, float roundness) : Button(text, buttonColor, size, position, roundness, false) {}

Button::Button(Text text, ButtonColor buttonColor, Vector2 size, Vector2 position) : Button(text, buttonColor, size, position, 0.25f) {}

Button::Button(Text text, ButtonColor buttonColor) : Button(text, buttonColor, {300, 300}, {(float)GetScreenWidth() / 2.0f - 150.0f, (float)GetScreenHeight() / 2.0f - 150.0f}) {}

Button::Button() : Button(Text(), ButtonColor{WHITE, WHITE, BLACK, BLACK, WHITE, WHITE}) {}


void Button::Update(const float &delta) {
    float touchX = (float)GetTouchX();
    float touchY = (float)GetTouchY();

    if (Global::pressedTimer > 0.0f) {
        if (touchX > position.x && touchX < position.x + size.x && touchY > position.y && touchY < position.y + size.y) {
            inHitbox = true;

            if (!mute) {
                if (!isHoverSoundPlayed) {
                    PlaySound(*AssetManager::GetSound(AssetManager::SOUND::SOUND_BUTTON_HOVER));
                    isHoverSoundPlayed = true;
                }
            }
        }
        else {
            inHitbox = false;
            isHoverSoundPlayed = false;
        }

        if (inHitbox) {
            if (Global::pressedTimer == delta) {
                inHitboxFromBeginning = true;
            }
            SetPressedColors();
        } else {
            SetReleasedColors();
        }
    }

    if (Global::pressedTimer == 0.0f) {
        if (inHitboxFromBeginning && inHitbox) {
            isPressed = true;
        }
        SetReleasedColors();
        inHitboxFromBeginning = false;
        isHoverSoundPlayed = false;
    }
}

void Button::Draw() {
    if (!onlyOutline)
        DrawRectangleRounded({position.x, position.y, size.x, size.y}, roundness, 0, Color{curr_color_fill.r, curr_color_fill.g, curr_color_fill.b, alpha});
    DrawRectangleRoundedLinesEx({position.x, position.y, size.x, size.y}, roundness, 0, 8.0f, Color{curr_color_outline.r, curr_color_outline.g, curr_color_outline.b, alpha});

    if (mango) {
        text.DrawMango();
    } else {
        text.Draw();
    }
}


void Button::CenterX() {
    position.x = (float)GetScreenWidth() / 2.0f - size.x / 2.0f;
    ValuesChanged();
}

void Button::CenterY() {
    position.y = (float)GetScreenHeight() / 2.0f - size.y / 2.0f;
    ValuesChanged();
}

void Button::ToggleOnlyOutline() {
    onlyOutline = !onlyOutline;
}

void Button::ToggleMute() {
    mute = !mute;
}

// Getters & Setters
bool Button::IsPressed() {
    if (isPressed) {
        isPressed = false;
        if(!mute)
            PlaySound(*AssetManager::GetSound(AssetManager::SOUND::SOUND_BUTTON_PRESS));
        return true;
    }
    return false;
}

void Button::SetSize(Vector2 size) {
    Button::size = size;
    ValuesChanged();
}

void Button::SetPosition(Vector2 position) {
    Button::position = position;
    ValuesChanged();
}

void Button::SetAlpha(uint8_t alpha) {
    Button::alpha = alpha;
}

Vector2 Button::GetSize() {
    return size;
}

Vector2 Button::GetPosition() {
    return position;
}


void Button::ValuesChanged() {
    Button::text.SetPosition({
        Button::position.x + Button::size.x / 2.0f - (mango ? Button::text.GetSizeMango().x : Button::text.GetSize().x) / 2.0f,
        Button::position.y + Button::size.y / 2.0f - (mango ? Button::text.GetSizeMango().y : Button::text.GetSize().y) / 2.0f
    });
}

void Button::SetPressedColors() {
    text.SetColor(buttonColor.text_color_pressed);
    curr_color_fill = buttonColor.color_pressed_fill;
    curr_color_outline = buttonColor.color_pressed_outline;
}

void Button::SetReleasedColors() {
    text.SetColor(buttonColor.text_color_released);
    curr_color_fill = buttonColor.color_released_fill;
    curr_color_outline = buttonColor.color_released_outline;
}


Vector2 Button::GetDefaultButtonSize() {
    return {(float)GetScreenWidth() * 0.75f, (float)GetScreenHeight() * 0.075f};
}

Button::ButtonColor Button::GetDefaultButtonColor(DEFAULT_BUTTON_COLOR defButtonColor) {
    switch (defButtonColor) {
        case DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_RED:
            return ButtonColor{
                    Color{55, 17, 32, 255},
                    Color{99, 30, 58, 255},
                    Color{99, 30, 58, 255},
                    Color{44, 13, 26, 255},
                    Color{44, 13, 26, 255},
                    Color{44, 13, 26, 255}
            };
        case DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_GREEN:
            return ButtonColor{
                    Color{53, 79, 82, 255},
                    Color{82, 121, 111, 255},
                    Color{82, 121, 111, 255},
                    Color{47, 62, 70, 255},
                    Color{47, 62, 70, 255},
                    Color{47, 62, 70, 255}
            };
        case DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_GRAY:
            return ButtonColor{
                    Color{27, 31, 44, 255},
                    Color{60, 66, 91, 255},
                    Color{60, 66, 91, 255},
                    Color{22, 26, 37, 255},
                    Color{22, 26, 37, 255},
                    Color{22, 26, 37, 255}
            };
        case DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_EMPTY:
            return ButtonColor{
                Color{0, 0, 0, 0},
                Color{0, 0, 0, 0},
                Color{0, 0, 0, 0},
                Color{0, 0, 0, 0},
                Color{0, 0, 0, 0},
                Color{0, 0, 0, 0}
            };
    }
}