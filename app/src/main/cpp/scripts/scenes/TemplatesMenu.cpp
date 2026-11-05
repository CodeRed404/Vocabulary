//
// Created by codered404 on 03.11.26.
//

#include "TemplatesMenu.h"

TemplatesMenu::TemplatesMenu() : Scene() {
    // Texts
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();

    heading = std::make_unique<Text>(
            "Templates",
            AssetManager::FONT::FONT_HEADER,
            200,
            10,
            Color{48, 25, 52, 255}
    );
    heading->SetPosition(Vector2{
            screenWidth / 2.0f - heading->GetSize().x / 2.0f,
            200
    });


    // Buttons

    Vector2 button_size = {800, 150};
    float button_y_distance = 50;

    button_back = std::make_unique<Button>();

    *button_back = Button(
            Text("<-", AssetManager::FONT::FONT_HEADER, 85, 3, RED),
            Button::ButtonColor{
                    Color{186, 31, 51, 255},
                    Color{205, 93, 103, 255},
                    Color{205, 93, 103, 255},
                    Color{65, 11, 19, 255},
                    Color{65, 11, 19, 255},
                    Color{65, 11, 19, 255}
            },
            button_size,
            {0, (float)GetScreenHeight() - button_size.y - 100}
    );
    button_back->CenterX();
}


void TemplatesMenu::Update(const float &delta) {
    UpdateUI(delta);
}

void TemplatesMenu::UpdateUI(const float &delta) {
    button_back->Update(delta);

    if (button_back->IsPressed()) {
        SceneManager::PopScene();
    }
}

void TemplatesMenu::Draw() {
    DrawUI();
}

void TemplatesMenu::DrawUI() {
    heading->Draw();

    button_back->Draw();
}