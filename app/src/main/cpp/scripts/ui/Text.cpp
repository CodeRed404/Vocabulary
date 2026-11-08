//
// Created by codered404 on 01.11.26.
//

#include "Text.h"
#include "../Global.h"

// Constructors

Text::Text(std::string text, AssetManager::FONT font, float fontSize, float spacing, Color color) {
    Text::text = text;
    Text::font = font;
    Text::fontSize = fontSize;
    Text::spacing = spacing;
    Text::color = color;

    ValuesChanged();
}

Text::Text() : Text("placeholder", AssetManager::FONT::FONT_DEFAULT_REGULAR, 50.0f, 10.0f, RED) {

}

// Updates & Draws

void Text::Draw() {
    DrawTextPro(*AssetManager::GetFont(font), text.c_str(), position, Vector2{0, 0}, 0.0f, fontSize, spacing, color);
}

void Text::DrawMango() {
    DrawTextPro(*AssetManager::GetFont(AssetManager::FONT::FONT_MANGO_FILL), text.c_str(), position, Vector2{0, 0}, 0.0f, fontSize, spacing, color);
    DrawTextPro(*AssetManager::GetFont(AssetManager::FONT::FONT_MANGO_SCRIBBLE), text.c_str(), position, Vector2{0, 0}, 0.0f, fontSize, spacing, Global::MakeColorLighter(color, 0.25f));
    DrawTextPro(*AssetManager::GetFont(AssetManager::FONT::FONT_MANGO_RG), text.c_str(), position, Vector2{0, 0}, 0.0f, fontSize, spacing, Global::MakeColorDarker(color, 0.25f));
}

// Getters & Setters {
Vector2 Text::GetSize() {
    return size;
}

Vector2 Text::GetSizeMango() {
    return sizeMango;
}

Vector2 Text::GetPosition() {
    return position;
}

float Text::GetFontSize() {
    return fontSize;
}

Color Text::GetColor() {
    return color;
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
    sizeMango = MeasureTextEx(*AssetManager::GetFont(AssetManager::FONT_MANGO_RG), text.c_str(), fontSize, spacing);
}