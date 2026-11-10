//
// Created by codered404 on 03.11.26.
//

#include "TemplatesMenu.h"
#include "../vocabs/Templates.h"
#include "../vocabs/TrainScene.h"
#include "../CodeRedColors.h"

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

    button_back = std::make_unique<Button>();

    *button_back = Button(
            Text("Back", AssetManager::FONT::FONT_BUTTON, 85, 3, RED),
            Button::GetDefaultButtonColor(Button::DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_RED),
            {200, 125},
            {100, 100}
    );

    // Template Buttons
    float button_y_distance = 20;

    for (int i = 0; i < Templates::Count(); i++) {
        template_buttons.push_back(std::make_unique<Button>());
        *template_buttons[i] = Button(
            Text(Templates::GetTemplatesAddr()->at(i).name, AssetManager::FONT::FONT_BUTTON, 85, 3, RED),
            Button::ButtonColor{
                    Color{0, 0, 0, 255},
                    Color{0, 0, 0, 255},
                    Color{175, 80, 10, 255},
                    Color{100, 45, 3, 255},
                    Color{100, 45, 3, 255},
                    Color{100, 45, 3, 255}
            },
            button_size,
            {0, (float)GetScreenHeight() / 4.0f + (i * (button_size.y + button_y_distance))}
        );
        template_buttons[i]->CenterX();
    }
}


void TemplatesMenu::Update(const float &delta) {
    UpdateUI(delta);
}

void TemplatesMenu::UpdateUI(const float &delta) {
    bool anyTemplateButtonIsPressed = false;
    for (int i = 0; i < template_buttons.size(); i++) {
        template_buttons[i]->Update(delta);

        if (template_buttons[i]->IsPressed()) {
            SceneManager::AddScene(new TrainScene(&Templates::GetTemplatesAddr()->at(i)));
            anyTemplateButtonIsPressed = true;
            break;
        }
    }

    button_back->Update(delta);

    if (!anyTemplateButtonIsPressed) {
        if (button_back->IsPressed()) {
            SceneManager::PopScene();
            return;
        }
    }
}

void TemplatesMenu::Draw() {
    DrawUI();
}

void TemplatesMenu::DrawUI() {
    heading->DrawMango();

    for (int i = 0; i < template_buttons.size(); i++) {
        template_buttons[i]->Draw();
    }

    button_back->Draw();
}