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

        void Update(const float& delta);
        void Draw();

        Vector2 GetSize();
        Vector2 GetPosition();
        void SetText(std::string text);
        void SetFont(AssetManager::FONT font);
        void SetFontSize(float fontSize);
        void SetSpacing(float spacing);
        void SetColor(Color color);
        void SetPosition(Vector2 position);
    private:
        std::string text;
        AssetManager::FONT font;
        float fontSize;
        float spacing;
        Color color;
        Vector2 size;
        Vector2 position;

        void ValuesChanged();
};


#endif //VOCABULARY_TEXT_H
