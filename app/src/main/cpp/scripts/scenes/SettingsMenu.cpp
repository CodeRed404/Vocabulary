//
// Created by codered404 on 10.11.26.
//

#include "raylib.h"
#include "../Manager.h"
#include "SceneManager.h"
#include "SettingsMenu.h"
#include "../vocabs/Templates.h"
#include "../CodeRedColors.h"
#include "thread"

SettingsMenu::SettingsMenu() {
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();

    // Texts
    heading = std::make_unique<Text>(
            "Settings",
            AssetManager::FONT::FONT_HEADER,
            200,
            10,
            Color{55, 55, 55, 255}
    );
    heading->SetPosition(Vector2{
            screenWidth / 2.0f - heading->GetSize().x / 2.0f,
            100
    });

    // Buttons
    button_inv_sync_templates = std::make_unique<Button>();
    button_back = std::make_unique<Button>();

    float fS; // fontSize
    float fS_y;

    fS = Text::GetFontSizeToFitWidth(*AssetManager::GetFont(AssetManager::FONT::FONT_BUTTON), "Sync Templates", 85, Button::GetDefaultButtonSize().x * 0.6, 3);
    fS_y = Text::GetFontSizeToFitHeight(*AssetManager::GetFont(AssetManager::FONT::FONT_BUTTON), "Sync Templates", 85, Button::GetDefaultButtonSize().y * 0.6, 3);
    if (fS > fS_y) {
        fS = fS_y;
    }
    *button_inv_sync_templates = Button(
            Text("Sync Templates", AssetManager::FONT::FONT_BUTTON, fS, 3, CR_C_EMPTY),
            Button::GetDefaultButtonColor(Button::DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_GRAY),
            Button::GetDefaultButtonSize(),
            {0, screenHeight * 0.2f}
    );
    button_inv_sync_templates->CenterX();
    button_inv_sync_templates->ToggleOnlyOutline();

    fS = Text::GetFontSizeToFitWidth(*AssetManager::GetFont(AssetManager::FONT::FONT_BUTTON), "Back", 85, Button::GetDefaultButtonSize().x * 0.6, 3);
    fS_y = Text::GetFontSizeToFitHeight(*AssetManager::GetFont(AssetManager::FONT::FONT_BUTTON), "Back", 85, Button::GetDefaultButtonSize().y * 0.6, 3);
    if (fS > fS_y) {
        fS = fS_y;
    }
    *button_back = Button(
            Text("Back", AssetManager::FONT::FONT_BUTTON, fS, 3, RED),
            Button::GetDefaultButtonColor(Button::DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_RED),
            Button::GetDefaultButtonSize(),
            {0, 0}
    );
    button_back->CenterX();
    button_back->SetPosition(Vector2{button_back->GetPosition().x, screenHeight - button_back->GetSize().y - 30});
}

void SettingsMenu::Update(const float &delta) {
    UpdateUI(delta);
}

void SettingsMenu::UpdateUI(const float &delta) {
    button_inv_sync_templates->Update(delta);
    button_back->Update(delta);

    if (button_inv_sync_templates->IsPressed()) {
        SyncTemplates(delta);
    } else if (button_back->IsPressed()) {
        SceneManager::PopScene();
    }
}

void SettingsMenu::Draw() {
    DrawUI();
}

void SettingsMenu::DrawUI() {
    heading->DrawMango();

    button_inv_sync_templates->Draw();
    button_back->Draw();
}


void SettingsMenu::SyncTemplates(const float &delta) {
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
        ClearBackground(BLACK);
        Manager::DrawBackground();
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