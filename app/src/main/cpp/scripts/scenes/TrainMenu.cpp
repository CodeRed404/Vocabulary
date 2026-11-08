//
// Created by codered404 on 03.11.26.
//

#include "TrainMenu.h"

TrainMenu::TrainMenu() : Scene() {
    // Texts
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();

    heading = std::make_unique<Text>(
            "Train",
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

    button_templates_menu = std::make_unique<Button>();
    button_userVocabs_menu = std::make_unique<Button>();
    button_back = std::make_unique<Button>();

    Vector2 button_size = {800, 150};
    float button_y_distance = 50;

    *button_templates_menu = Button(
            Text("Templates", AssetManager::FONT::FONT_BUTTON, 85, 3, WHITE),
            Button::DefaultButtonColor,
            button_size,
            {0, 0.3f * (float)GetScreenHeight()}
    );
    button_templates_menu->CenterX();
    button_templates_menu->CenterY();

    *button_userVocabs_menu = Button(
            Text("myVocabs", AssetManager::FONT::FONT_BUTTON, 85, 3, WHITE),
            Button::DefaultButtonColor,
            button_size,
            {0, button_templates_menu->GetPosition().y + button_templates_menu->GetSize().y + button_y_distance}
    );
    button_userVocabs_menu->CenterX();

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
            {0, (float)GetScreenHeight() - button_size.y - 100/*button_userVocabs_menu->GetPosition().y + button_userVocabs_menu->GetSize().y + button_y_distance*/}
    );
    button_back->CenterX();
}


void TrainMenu::Update(const float &delta) {
    UpdateUI(delta);
}

void TrainMenu::UpdateUI(const float &delta) {
    button_templates_menu->Update(delta);
    button_userVocabs_menu->Update(delta);
    button_back->Update(delta);

    if (button_templates_menu->IsPressed()) {
        SceneManager::AddScene(new TemplatesMenu());
    } else if (button_userVocabs_menu->IsPressed()) {
        SceneManager::AddScene(new VocabsMenu(VocabsMenu::VOCABS_MENU_MODE::VOCABS_MENU_TRAIN));
    } else if (button_back->IsPressed()) {
        SceneManager::PopScene();
    }
}

void TrainMenu::Draw() {
    DrawUI();
}

void TrainMenu::DrawUI() {
    heading->DrawMango();

    button_templates_menu->Draw();
    button_userVocabs_menu->Draw();
    button_back->Draw();
}