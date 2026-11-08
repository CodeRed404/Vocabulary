//
// Created by codered404 on 03.11.26.
//

#include "VocabsMenu.h"

VocabsMenu::VocabsMenu(VocabsMenu::VOCABS_MENU_MODE mode) {
    VocabsMenu::mode = mode;

    // Texts
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();

    heading = std::make_unique<Text>(
            (mode == VOCABS_MENU_MODE::VOCABS_MENU_TRAIN ? "Train Vocabs" : "Edit Vocabs"),
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
            Text("Back", AssetManager::FONT::FONT_BUTTON, 85, 3, RED),
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


void VocabsMenu::Update(const float &delta) {
    UpdateUI(delta);
}

void VocabsMenu::UpdateUI(const float &delta) {
    button_back->Update(delta);

    if (button_back->IsPressed()) {
        SceneManager::PopScene();
        return;
    }
}

void VocabsMenu::Draw() {
    DrawUI();
}

void VocabsMenu::DrawUI() {
    heading->DrawMango();

    button_back->Draw();
}