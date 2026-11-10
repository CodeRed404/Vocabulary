//
// Created by codered404 on 08.11.26.
//

#include "TrainScene.h"
#include "../scenes/SceneManager.h"

TrainScene::TrainScene(Template *template_ptr) {
    TrainScene::template_ptr = template_ptr;

    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();

    // train
    currVocab = TrainScene::template_ptr->vocabs[0];
    defaultVocabFontSize = 100;
    tapAlpha = 0;
    tapUp = true;
    cardSize = {1000, 1000};
    cardRect = {(float)GetScreenWidth() / 2.0f - cardSize.x / 2.0f, (float)GetScreenHeight() / 3.0f - cardSize.y / 2.0f, cardSize.x, cardSize.y};
    currWordIsEN = true;
    EN_to_DE = true;

    cardButton = std::make_unique<Button>();
    *cardButton = Button(
            Text("", AssetManager::FONT::FONT_BUTTON, 0, 0, WHITE),
            Button::ButtonColor{
                    Color{0, 0, 0, 0},
                    Color{0, 0, 0, 0},
                    Color{0, 0, 0, 0},
                    Color{0, 0, 0, 0},
                    Color{0, 0, 0, 0},
                    Color{0, 0, 0, 0}
            },
            {cardRect.width, cardRect.height},
            {cardRect.x, cardRect.y}
    );
    cardButton->ToggleMute();

    tapText = Text(
        "Tap",
        AssetManager::FONT::FONT_DEFAULT_BOLD,
        75,
        10,
        WHITE
    );
    tapText.SetPosition(Vector2{
        cardRect.x + cardRect.width / 2.0f - tapText.GetSize().x / 2.0f,
        cardRect.y + cardRect.height - tapText.GetSize().y - 30.0f
    });

    currVocabText = Text(
            currVocab.en,
            AssetManager::FONT::FONT_DEFAULT_BOLD,
            defaultVocabFontSize,
            10,
            WHITE
    );
    currVocabText.SetPosition(Vector2{
            cardRect.x + cardRect.width / 2.0f - currVocabText.GetSize().x / 2.0f,
            cardRect.y + cardRect.height / 2.0f - currVocabText.GetSize().y / 2.0f
    });

    currVocabIDText = Text(
        std::to_string(currVocab.id + 1),
        AssetManager::FONT::FONT_DEFAULT_BOLD,
        100,
        10,
        WHITE
    );
    currVocabIDText.SetPosition(Vector2{
        cardRect.x + cardRect.width / 2.0f - currVocabIDText.GetSize().x / 2.0f,
        cardRect.y + 50
    });

    button_switchLanguage = std::make_unique<Button>();
    button_random = std::make_unique<Button>();
    button_previous = std::make_unique<Button>();
    button_next = std::make_unique<Button>();
    button_first = std::make_unique<Button>();

    /*
    // contrast
    Button::ButtonColor confButtonColor = {
        Color{0, 255, 255, 255},
        Color{0, 255, 255, 255},
        Color{0, 0, 0, 255},
        Color{111, 143, 175, 255},
        Color{0, 255, 255, 255},
        Color{111, 143, 175, 255}
    };*/
    Button::ButtonColor confButtonColor = {
            Color{142, 158, 174, 255},
            Color{142, 158, 174, 255},
            Color{54, 69, 79, 255},
            Color{24, 39, 49, 255},
            Color{24, 39, 49, 255},
            Color{24, 39, 49, 255}
    };

    Vector2 nextButtonSize = {(float)screenWidth - 200, 200};
    Vector2 nextButtonPos = {screenWidth / 2.0f - nextButtonSize.x / 2.0f, screenHeight - nextButtonSize.y - 30.0f};
    float buttonHalfAndMore = 10.0f;
    float buttonGroundDistance = 30.0;
    float buttonYDistance = 20.0f;
    *button_random = Button(
            Text("Random", AssetManager::FONT::FONT_DEFAULT_BOLD, 125, 3, RED),
            confButtonColor,
            nextButtonSize,
            {nextButtonPos.x, nextButtonPos.y - 2 * nextButtonSize.y - 2 * buttonYDistance},
            0.2f
    );
    *button_previous = Button(
            Text("Previous", AssetManager::FONT::FONT_DEFAULT_BOLD, 125, 3, RED),
            confButtonColor,
            {nextButtonSize.x / 2.0f - buttonHalfAndMore, nextButtonSize.y},
            {nextButtonPos.x, nextButtonPos.y - nextButtonSize.y - buttonYDistance},
            0.2f
    );
    *button_next = Button(
            Text("Next", AssetManager::FONT::FONT_DEFAULT_BOLD, 125, 3, RED),
            confButtonColor,
            {nextButtonSize.x / 2.0f - buttonHalfAndMore, nextButtonSize.y},
            {nextButtonPos.x + nextButtonSize.x - (nextButtonSize.x / 2.0f - buttonHalfAndMore), nextButtonPos.y - nextButtonSize.y - buttonYDistance},
            0.2f
    );
    *button_first = Button(
            Text("First", AssetManager::FONT::FONT_DEFAULT_BOLD, 125, 3, RED),
            confButtonColor,
            nextButtonSize,
            nextButtonPos,
            0.2f
    );
    *button_switchLanguage = Button(
            Text("Switch Language", AssetManager::FONT::FONT_DEFAULT_BOLD, 125, 3, RED),
            confButtonColor,
            {nextButtonSize.x / 2.0f - buttonHalfAndMore, nextButtonSize.y},
            {button_random->GetPosition().x, button_random->GetPosition().y - nextButtonSize.y - buttonYDistance},
            0.2f
    );


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
            {(float)GetScreenWidth() - 125, 50},
            0.5f
    );

    *button_back = Button(
            Text("Back", AssetManager::FONT::FONT_BUTTON, 85, 3, RED),
            Button::GetDefaultButtonColor(Button::DEFAULT_BUTTON_COLOR::DEFAULT_BUTTON_COLOR_RED),
            {250, 100},
            {25, 50},
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

        if (!button_list_vocabs->IsPressed()) {
            if (button_back->IsPressed()) {
                SceneManager::PopScene();
                return;
            }
        }
    }

    UpdateCard(delta);
}

void TrainScene::UpdateCard(const float &delta) {
    cardButton->Update(delta);
    // --
    button_switchLanguage->Update(delta);
    button_previous->Update(delta);
    button_first->Update(delta);
    button_random->Update(delta);
    button_next->Update(delta);

    if (!button_list_vocabs->IsPressed() && !button_back->IsPressed()) {
        bool any = false;
        if (cardButton->IsPressed() && !help_info) {
            if (EN_to_DE) {
                currVocabText.SetText(currWordIsEN ? currVocab.de : currVocab.en);
            } else {
                currVocabText.SetText(currWordIsEN ? currVocab.en : currVocab.de);
            }
            currWordIsEN = !currWordIsEN;
            any = true;
        } else if (button_switchLanguage->IsPressed()) {
            EN_to_DE = !EN_to_DE;
        } else if (button_random->IsPressed()) {
            currVocab = template_ptr->vocabs[rand() % template_ptr->vocabs.size()];
            currWordIsEN = true;
            any = true;
        } else if (button_previous->IsPressed()) {
            currVocab = template_ptr->vocabs[currVocab.id - 1 >= 0 ? currVocab.id - 1 : template_ptr->vocabs.size() - 1];
            currWordIsEN = true;
            any = true;
        } else if (button_next->IsPressed()) {
            currVocab = template_ptr->vocabs[currVocab.id + 1 < template_ptr->vocabs.size() ? currVocab.id + 1 : 0];
            currWordIsEN = true;
            any = true;
        } else if (button_first->IsPressed()) {
            currVocab = template_ptr->vocabs[0];
            currWordIsEN = true;
            any = true;
        }

        if (any) {
            currVocabText.SetFontSize(defaultVocabFontSize);
            currVocabText.SetText(currWordIsEN ? currVocab.en : currVocab.de);

            if (currVocabText.GetSize().x > cardRect.width - 60) {
                while (currVocabText.GetSize().x > cardRect.width - 60) {
                    currVocabText.SetFontSize(currVocabText.GetFontSize() - 1);
                }
            }

            currVocabText.SetPosition({
                cardRect.x + cardRect.width / 2.0f - currVocabText.GetSize().x / 2.0f,
                cardRect.y + cardRect.height / 2.0f - currVocabText.GetSize().y / 2.0f
            });

            currVocabIDText.SetText(std::to_string(currVocab.id + 1));
            currVocabIDText.SetPosition(Vector2{
                    cardRect.x + cardRect.width / 2.0f - currVocabIDText.GetSize().x / 2.0f,
                    cardRect.y + 50
            });
        }
    }

    // tap
    if (tapUp) {
        if (tapAlpha < 200) {
            for (int i = 0; i < 5; i++) {
                if (tapAlpha < 200) {
                    tapAlpha++;
                }
            }
        } else {
            tapUp = !tapUp;
        }
    } else {
        if (tapAlpha > 50) {
            for (int i = 0; i < 5; i++) {
                if (tapAlpha > 50) {
                    tapAlpha--;
                }
            }
        } else {
            tapUp = !tapUp;
        }
    }

    tapText.SetColor(ColorAlpha(tapText.GetColor(), (float)tapAlpha / 255.0f));
}

void TrainScene::Draw() {
    if (!help_info) {
        button_back->Draw();

        // train card
        DrawRectangleRounded(cardRect, 0.075f, 0, Color{50, 50, 50, 100});
        DrawRectangleRoundedLinesEx(cardRect, 0.075f, 0, 8.0f, Color{255, 255, 255, 100});
        tapText.Draw();
        currVocabIDText.Draw();
        currVocabText.Draw();
    } else {
        Vector2 panel_pos = {75.0f, 150.0f};
        Vector2 panel_size = {(float)GetScreenWidth() - panel_pos.x * 2, (float)GetScreenHeight() * (2.0f/3.0f)/*(float)GetScreenHeight() - panel_pos.y * 2*/};
        DrawRectangleRounded({panel_pos.x, panel_pos.y, panel_size.x, panel_size.y}, 0.075f, 0, Color{50, 50, 50, 75});

        Vector2 vocabPos = {panel_pos.x + 75, panel_pos.y + 150};

        DrawTextPro(*AssetManager::GetFont(AssetManager::FONT::FONT_DEFAULT_BOLD), (EN_to_DE ? "ID: EN = DE" : "ID: DE = EN"), {vocabPos.x, vocabPos.y - 100}, {0, 0}, 0, 80, 5, GREEN);
        for (int i = 0; i < template_ptr->vocabs.size(); i++) {
            Vocab vocab = template_ptr->vocabs[i];
            Color color = WHITE;

            if (vocab.id == currVocab.id) {
                color = BLUE;
            }

            float fontSize = 50;
            float spacing = 5;

            Vector2 measuredText = MeasureTextEx(*AssetManager::GetFont(AssetManager::FONT::FONT_DEFAULT_REGULAR), (std::to_string(vocab.id + 1) + ": " + vocab.en + " = " + vocab.de).c_str(), fontSize, spacing);
            if (measuredText.x > panel_pos.x + panel_size.x - vocabPos.x - 30) {
                while (measuredText.x > panel_pos.x + panel_size.x - vocabPos.x - 30) {
                    fontSize--;
                    if (EN_to_DE) {
                        measuredText = MeasureTextEx(*AssetManager::GetFont(AssetManager::FONT::FONT_DEFAULT_REGULAR), (std::to_string(vocab.id + 1) + ": " + vocab.en + " = " + vocab.de).c_str(), fontSize, spacing);
                    } else {
                        measuredText = MeasureTextEx(*AssetManager::GetFont(AssetManager::FONT::FONT_DEFAULT_REGULAR), (std::to_string(vocab.id + 1) + ": " + vocab.de + " = " + vocab.en).c_str(), fontSize, spacing);
                    }
                }
            }

            DrawTextPro(*AssetManager::GetFont(AssetManager::FONT::FONT_DEFAULT_REGULAR), (std::to_string(vocab.id + 1) + ": " + vocab.en + " = " + vocab.de).c_str(), vocabPos, {0, 0}, 0, fontSize, spacing, color);
            vocabPos.y += measuredText.y + 5;
        }
    }

    button_list_vocabs->Draw();

    button_switchLanguage->Draw();
    button_previous->Draw();
    button_first->Draw();
    button_random->Draw();
    button_next->Draw();
}