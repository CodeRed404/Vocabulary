//
// Created by codered404 on 01.11.26.
//

#include "Menu.h"

Menu::Menu() {
    want_to_quit = false;

    // Texts
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();

    heading = std::make_unique<Text>(
        "Vocabulary",
        AssetManager::FONT::FONT_HEADER,
        200,
        10,
        Color{48, 25, 52, 255}
    );
    heading->SetPosition(Vector2{
        screenWidth / 2.0f - heading->GetSize().x / 2.0f,
        200
    });
    heading->SetPosition({0, 0});

    developer_credit = std::make_unique<Text>(
        "developed by CodeRed404",
        AssetManager::FONT::FONT_HEADER,
        65,
        10,
        RED
    );
    developer_credit->SetPosition(Vector2{
        screenWidth / 2.0f - developer_credit->GetSize().x / 2.0f,
        screenHeight - developer_credit->GetSize().y * 2.0f
    });


    // Buttons

    button_train = std::make_unique<Button>();
    button_vocabs = std::make_unique<Button>();
    button_quit = std::make_unique<Button>();

    float button_y_distance = 50;

    *button_train = Button(
        Text("Train", AssetManager::FONT::FONT_HEADER, 85, 3, WHITE),
        Button::DefaultButtonColor,
        {800, 150},
        {0, 0.3f * (float)GetScreenHeight()}
    );
    button_train->CenterX();
    button_train->CenterY();

    *button_vocabs = Button(
            Text("Vocabs", AssetManager::FONT::FONT_HEADER, 85, 3, WHITE),
            Button::DefaultButtonColor,
            {800, 150},
            {0, button_train->GetPosition().y + button_train->GetSize().y + button_y_distance}
    );
    button_vocabs->CenterX();

    *button_quit = Button(
            Text("QUIT", AssetManager::FONT::FONT_HEADER, 85, 3, RED),
            Button::DefaultButtonColor,
            {800, 150},
            {0, button_vocabs->GetPosition().y + button_vocabs->GetSize().y + button_y_distance}
    );
    button_quit->CenterX();
}

void Menu::Update(const float &delta) {
    UpdateUI(delta);
    heading->SetText(Global::text); // nur fuer testen
}

void Menu::UpdateUI(const float &delta) {
    button_train->Update(delta);
    button_vocabs->Update(delta);
    button_quit->Update(delta);

    if (button_train->IsPressed()) {
        SceneManager::AddScene(new TrainMenu());
    } else if (button_vocabs->IsPressed()) {
        SceneManager::AddScene(new VocabsMenu(VocabsMenu::VOCABS_MENU_MODE::VOCABS_MENU_EDIT));
    } else if (button_quit->IsPressed()) {
        want_to_quit = true;
    }

    if (want_to_quit) {
        if (!IsSoundPlaying(*AssetManager::GetSound(AssetManager::SOUND::SOUND_BUTTON_PRESS))) {
            Global::exitProgram = true;
        }
    }
}

void Menu::Draw() {
    DrawUI();
}

void Menu::DrawUI() {
    heading->Draw();
    developer_credit->Draw();

    button_train->Draw();
    button_vocabs->Draw();
    button_quit->Draw();
}