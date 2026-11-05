//
// Created by codered404 on 01.11.26.
//

#include "Text.h"

// Constructors

Text::Text(std::string text, AssetManager::FONT font, float fontSize, float spacing, Color color) {
    Text::text = text;
    Text::font = font;
    Text::fontSize = fontSize;
    Text::spacing = spacing;
    Text::color = color;

    ValuesChanged();
}

Text::Text() : Text("placeholder", AssetManager::FONT::FONT_DEFAULT, 50.0f, 10.0f, RED) {

}

// Updates & Draws

void Text::Update(const float &delta) {

}

void Text::Draw() {
    DrawTextPro(*AssetManager::GetFont(font), text.c_str(), position, Vector2{0, 0}, 0.0f, fontSize, spacing, color);
}

// Getters & Setters {
Vector2 Text::GetSize() {
    return size;
}

Vector2 Text::GetPosition() {
    return position;
}

void Text::SetText(std::string text) {
    Text::text = text;
    ValuesChanged();
}

void Text::SetFont(AssetManager::FONT font) {
    Text::font = font;
    ValuesChanged();
}

void Text::SetFontSize(float fontSize) {
    Text::fontSize = fontSize;
    ValuesChanged();
}

void Text::SetSpacing(float spacing) {
    Text::spacing = spacing;
    ValuesChanged();
}

void Text::SetColor(Color color) {
    Text::color = color;
}

void Text::SetPosition(Vector2 position) {
    Text::position = position;
}
// }

void Text::ValuesChanged() {
    size = MeasureTextEx(*AssetManager::GetFont(font), text.c_str(), fontSize, spacing);
}