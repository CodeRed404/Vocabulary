//
// Created by codered404 on 03.11.26.
//

#include "TemplatesMenu.h"
#include "../vocabs/Templates.h"
#include "../vocabs/TrainScene.h"
#include "thread"

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

    button_sync_templates = std::make_unique<Button>();
    button_back = std::make_unique<Button>();

    *button_sync_templates = Button(
            Text("Sync", AssetManager::FONT::FONT_BUTTON, 85, 3, RED),
            Button::ButtonColor{
                    Color{186, 31, 51, 255},
                    Color{205, 93, 103, 255},
                    Color{205, 93, 103, 255},
                    Color{65, 11, 19, 255},
                    Color{65, 11, 19, 255},
                    Color{65, 11, 19, 255}
            },
            {200, 200},
            {(float)GetScreenWidth() - 300, 100}
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
            button_size,
            {0, (float)GetScreenHeight() - button_size.y - 100}
    );
    button_back->CenterX();

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

    button_sync_templates->Update(delta);
    button_back->Update(delta);

    if (!anyTemplateButtonIsPressed) {
        if (button_sync_templates->IsPressed()) {
            SyncTemplates(delta);
        } else if (button_back->IsPressed()) {
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
    button_sync_templates->Draw();
}


void TemplatesMenu::SyncTemplates(const float &delta) {
    // Load data
    std::thread nwThread(Templates::LoadTemplates);
    nwThread.detach();

    Global::isLoading = true;

    // Loading animation
    Texture2D loadingCircle = LoadTexture("textures/loading/loading_circle.png");
    float loadingCircleRotation = 0;
    float loadingCircleFactor = 0.75f;
    float loadingCircleSpeed = 350.0f;
    while (Global::isLoading) {
        BeginDrawing();
        this->Draw();
        DrawTexturePro(loadingCircle, {0, 0, (float)loadingCircle.width, (float)loadingCircle.height}, {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f, (float)loadingCircle.width * loadingCircleFactor, (float)loadingCircle.height * loadingCircleFactor}, {loadingCircle.width * loadingCircleFactor / 2.0f, loadingCircle.height * loadingCircleFactor / 2.0f}, loadingCircleRotation, WHITE);
        EndDrawing();
        loadingCircleRotation += loadingCircleSpeed * delta;
        if (loadingCircleRotation >= 360) {
            loadingCircleRotation = 0;
        }
    }
    UnloadTexture(loadingCircle);
}