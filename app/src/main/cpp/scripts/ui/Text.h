//
// Created by codered404 on 01.11.26.
//

#ifndef VOCABULARY_TEXT_H
#define VOCABULARY_TEXT_H

#include "raylib.h"
#include "../AssetManager.h"
#include "string"

class Text {
    public:
        Text(std::string text, AssetManager::FONT font, float fontSize, float spacing, Color color);
        Text();

        void Draw();
        void DrawMango();

        Vector2 GetSize();
        Vector2 GetSizeMango();
        Vector2 GetPosition();
        std::string GetText();
        float GetSpacing();
        float GetFontSize();
        AssetManager::FONT GetFont();
        Color GetColor();
        void SetText(std::string text);
        void SetFont(AssetManager::FONT font);
        void SetFontSize(float fontSize);
        void SetSpacing(float spacing);
        void SetColor(Color color);
        void SetPosition(Vector2 position);

        static float GetFontSizeToFitWidth(const Font &font, std::string text, float fontSize, float maxWidth, float spacing);
        static float GetFontSizeToFitHeight(const Font &font, std::string text, float fontSize, float maxHeight, float spacing);
    private:
        std::string text;
        AssetManager::FONT font;
        float fontSize;
        float spacing;
        Color color;
        Vector2 size;
        Vector2 sizeMango;
        Vector2 position;

        void ValuesChanged();
};


#endif //VOCABULARY_TEXT_H
