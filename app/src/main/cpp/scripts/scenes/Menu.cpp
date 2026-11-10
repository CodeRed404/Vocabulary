//
// Created by codered404 on 01.11.26.
//

#include "Menu.h"
#include "../CodeRedColors.h"

Menu::Menu() {
    want_to_quit = false;

    // Texts
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();

    heading = std::make_unique<Text>(
        "Vocabulary",
        AssetManager::FONT::FONT_HEADER,
        150,
        10,
        Color{48, 25, 52, 255}
    );
    heading->SetPosition(Vector2{
        screenWidth / 2.0f - heading->GetSize().x / 2.0f,
        100
    });

    developer_credit = std::make_unique<Text>(
        "developed by CodeRed404",
        AssetManager::FONT::FONT_HEADER,
        350,
        10,
        RED
    );
    developer_credit->SetFontSize(Text::GetFontSizeToFitWidth(*AssetManager::GetFont(developer_credit->GetFont()), developer_credit->GetText(), developer_credit->GetFontSize(), screenWidth * 0.45f, developer_credit->GetSpacing()));
    developer_credit->SetPosition(Vector2{
        screenWidth / 2.0f - developer_credit->GetSize().x / 2.0f,
        screenHeight - developer_credit->GetSize().y * 2.0f
    });


    // Buttons

    button_settings = std::make_unique<Button>();
    button_train = std::make_unique<Button>();
    button_vocabs = std::make_unique<Button>();
    button_quit = std::make_unique<Button>();

    Vector2 button_size = Button::GetDefaultButtonSize();
    float button_y_distance = 8;

    float button_settings_size = screenWidth * 0.1f;
    if (button_settings_size > 150) {
        button_settings_size = 150;
    } else if (button_settings_size < 50) {
        button_settings_size = 50;
    }
    std::string button_settings_text = "{}";
    float button_settings_spacing = 7;
    *button_settings = Button(
            Text(button_settings_text, AssetManager::FONT::FONT_BUTTON, Text::GetFontSizeToFitWidth(*AssetManager::GetFont(AssetManager::FONT::FONT_BUTTON), button_settings_text, 30, button_settings_size * 0.8f, button_settings_spacing), button_settings_spacing, RED),
            Button::GetDefaultButtonColor(Button::DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_GRAY),
            Vector2{button_settings_size, button_settings_size},
            {screenWidth - button_settings_size - 50, 50}
    );

    *button_train = Button(
        Text("Train", AssetManager::FONT::FONT_BUTTON, 85, 3, WHITE),
        Button::GetDefaultButtonColor(Button::DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_GREEN),
        button_size,
        {0, 0.3f * (float)GetScreenHeight()}
    );
    button_train->CenterX();
    button_train->CenterY();

    *button_vocabs = Button(
            Text("Vocabs", AssetManager::FONT::FONT_BUTTON, 85, 3, WHITE),
            Button::GetDefaultButtonColor(Button::DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_GREEN),
            button_size,
            {0, button_train->GetPosition().y + button_train->GetSize().y + button_y_distance}
    );
    button_vocabs->CenterX();

    *button_quit = Button(
            Text("QUIT", AssetManager::FONT::FONT_BUTTON, 85, 3, RED),
            Button::GetDefaultButtonColor(Button::DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_RED),
            button_size,
            {0, button_vocabs->GetPosition().y + button_vocabs->GetSize().y + button_y_distance}
    );
    button_quit->CenterX();

    // robot
    robot_is_texture_0 = true;
    robot_goes_to_right = true;
    robot_texture_switch_time = 0.1;
    robot_texture_switch_timer = robot_texture_switch_time;
    robot_x_pos = button_train->GetPosition().x;
    robot_y_pos = button_train->GetPosition().y - AssetManager::GetTexture(AssetManager::TEXTURE::TEXTURE_ROBOT_0)->height;
    robot_speed = 100;
}

void Menu::Update(const float &delta) {
    // robot
    robot_texture_switch_timer -= delta;
    if (robot_texture_switch_timer <= 0) {
        robot_is_texture_0 = !robot_is_texture_0;
        robot_y_pos = button_train->GetPosition().y - AssetManager::GetTexture((robot_is_texture_0 ? AssetManager::TEXTURE::TEXTURE_ROBOT_0 : AssetManager::TEXTURE::TEXTURE_ROBOT_1))->height;
        robot_texture_switch_timer = robot_texture_switch_time;
    }
    if (robot_goes_to_right) {
        robot_x_pos += robot_speed * delta;
        if (robot_x_pos + AssetManager::GetTexture(AssetManager::TEXTURE::TEXTURE_ROBOT_0)->width >= button_train->GetPosition().x + button_train->GetSize().x) {
            robot_goes_to_right = !robot_goes_to_right;
        }
    } else {
        robot_x_pos -= robot_speed * delta;
        if (robot_x_pos <= button_train->GetPosition().x) {
            robot_goes_to_right = !robot_goes_to_right;
        }
    }


    UpdateUI(delta);
}

void Menu::UpdateUI(const float &delta) {
    button_settings->Update(delta);
    button_train->Update(delta);
    button_vocabs->Update(delta);
    button_quit->Update(delta);

    if (button_settings->IsPressed()) {
        SceneManager::AddScene(new SettingsMenu());
    } else if (button_train->IsPressed()) {
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

    Texture2D robot_txr = *AssetManager::GetTexture(robot_is_texture_0 ? AssetManager::TEXTURE::TEXTURE_ROBOT_0 : AssetManager::TEXTURE::TEXTURE_ROBOT_1);
    DrawTextureRec(robot_txr, Rectangle{0, 0, (float)robot_txr.width * (robot_goes_to_right ? 1 : -1), (float)robot_txr.height}, Vector2{robot_x_pos, robot_y_pos}, WHITE);
}

void Menu::DrawUI() {
    heading->DrawMango();
    developer_credit->Draw();

    button_settings->Draw();
    button_train->Draw();
    button_vocabs->Draw();
    button_quit->Draw();
}