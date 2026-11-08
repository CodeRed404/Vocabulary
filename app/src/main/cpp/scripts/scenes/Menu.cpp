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
        Text("Train", AssetManager::FONT::FONT_BUTTON, 85, 3, WHITE),
        Button::DefaultButtonColor,
        {800, 150},
        {0, 0.3f * (float)GetScreenHeight()}
    );
    button_train->CenterX();
    button_train->CenterY();

    *button_vocabs = Button(
            Text("Vocabs", AssetManager::FONT::FONT_BUTTON, 85, 3, WHITE),
            Button::DefaultButtonColor,
            {800, 150},
            {0, button_train->GetPosition().y + button_train->GetSize().y + button_y_distance}
    );
    button_vocabs->CenterX();

    *button_quit = Button(
            Text("QUIT", AssetManager::FONT::FONT_BUTTON, 85, 3, RED),
            Button::DefaultButtonColor,
            {800, 150},
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

    Texture2D robot_txr = *AssetManager::GetTexture(robot_is_texture_0 ? AssetManager::TEXTURE::TEXTURE_ROBOT_0 : AssetManager::TEXTURE::TEXTURE_ROBOT_1);
    DrawTextureRec(robot_txr, Rectangle{0, 0, (float)robot_txr.width * (robot_goes_to_right ? 1 : -1), (float)robot_txr.height}, Vector2{robot_x_pos, robot_y_pos}, WHITE);
}

void Menu::DrawUI() {
    heading->DrawMango();
    developer_credit->Draw();

    button_train->Draw();
    button_vocabs->Draw();
    button_quit->Draw();
}