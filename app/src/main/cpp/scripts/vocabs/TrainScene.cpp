//
// Created by codered404 on 08.11.26.
//

#include "TrainScene.h"
#include "../scenes/SceneManager.h"

TrainScene::TrainScene(Template *template_ptr) {
    TrainScene::template_ptr = template_ptr;

    // Buttons
    Vector2 button_size = {800, 150};
    float button_y_distance = 50;

    button_list_vocabs = std::make_unique<Button>();
    button_back = std::make_unique<Button>();

    *button_list_vocabs = Button(
            Text("i", AssetManager::FONT::FONT_DEFAULT_BOLD, 85, 3, RED),
            Button::ButtonColor{
                    WHITE,
                    WHITE,
                    BLUE,
                    DARKBLUE,
                    DARKBLUE,
                    DARKBLUE
            },
            {100, 100},
            {(float)GetScreenWidth() - 125, 25},
            0.5f
    );

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
            {250, 100},
            {25, 25},
            0.75f
    );
}


void TrainScene::Update(const float &delta) {
    button_list_vocabs->Update(delta);

    if (button_list_vocabs->IsPressed()) {
        help_info = !help_info;
        button_list_vocabs->SetAlpha(help_info ? 75 : 255);
    }

    if (!help_info) {
        button_back->Update(delta);

        if (button_list_vocabs->IsPressed()) {
            // so the user can't press multiple buttons at the same time
        } else if (button_back->IsPressed()) {
            SceneManager::PopScene();
        }
    }
}

void TrainScene::Draw() {
    if (!help_info) {
        button_back->Draw();
    } else {
        float panel_pos = 75.0f;
        DrawRectangleRounded({panel_pos, panel_pos, (float)GetScreenWidth() - panel_pos * 2, (float)GetScreenHeight() - panel_pos * 2}, 0.075f, 0, Color{50, 50, 50, 75});

        Vector2 vocabPos = {125, 225};

        DrawTextPro(*AssetManager::GetFont(AssetManager::FONT::FONT_DEFAULT_BOLD), "ID: EN = DE", {vocabPos.x, vocabPos.y - 100}, {0, 0}, 0, 80, 5, GREEN);
        for (int i = 0; i < template_ptr->vocabs.size(); i++) {
            Vocab vocab = template_ptr->vocabs[i];
            DrawTextPro(*AssetManager::GetFont(AssetManager::FONT::FONT_DEFAULT_REGULAR), (std::to_string(vocab.id + 1) + ": " + vocab.en + " = " + vocab.de).c_str(), vocabPos, {0, 0}, 0, 45, 5, WHITE);
            vocabPos.y += 55;
        }
    }

    button_list_vocabs->Draw();
}