//
// Created by codered404 on 01.11.26.
//

#include "Manager.h"
#include "scenes/SceneManager.h"
#include "scenes/Menu.h"

std::string Manager::warning_text;
float Manager::warning_timer;
Color Manager::warning_color;
float Manager::warning_text_fontSize;
float Manager::warning_text_spacing;
Vector2 Manager::warning_text_size;
Vector2 Manager::warning_size;
Vector2 Manager::warning_position;
bool Manager::warning_appeard;
uint8_t Manager::warning_alpha;
float Manager::warning_alpha_timer;

void Manager::Update(const float& delta) {
    if (SceneManager::Empty()) {
        SceneManager::AddScene(new Menu());
    }
    SceneManager::Update(delta);

    UpdateWarning(delta);
}

void Manager::UpdateWarning(const float &delta) {
    if (warning_timer > 0) {
        warning_timer -= delta;
    }

    if (warning_timer > 0 || warning_alpha > 0) {
        if (warning_appeard) {
            if (warning_alpha_timer > 0) {
                warning_alpha_timer -= delta;
            }

            if (warning_timer <= 0) {
                warning_alpha--;
                for (int i = 0; i < 9; i++) {
                    if (warning_alpha > 0) {
                        warning_alpha--;
                    } else {
                        break;
                    }
                    warning_alpha_timer = WARNING_ALPHA_TIME;
                }
            }
        } else {
            if (warning_alpha < 255) {
                warning_alpha++;

                if (warning_alpha > 50) {
                    if (warning_alpha < 255) {
                        warning_alpha++;
                        if (warning_alpha < 255) {
                            warning_alpha++;
                        }
                    }
                }
            } else {
                warning_appeard = true;
            }
        }
    }
}

void Manager::Draw() {
    SceneManager::Draw();

    DrawWarning();
}

void Manager::DrawWarning() {
    if (warning_timer > 0 || warning_alpha > 0) {
        DrawRectangleRounded({warning_position.x, warning_position.y, warning_size.x, warning_size.y}, 0.5f, 0, ColorAlpha(warning_color, (float)warning_alpha / 255.0f));
        DrawTextPro(*AssetManager::GetFont(AssetManager::FONT::FONT_DEFAULT_BOLD), warning_text.c_str(), {warning_position.x + warning_size.x / 2.0f - warning_text_size.x / 2.0f, warning_position.y + warning_size.y / 2.0f - warning_text_size.y / 2.0f}, {0, 0}, 0, warning_text_fontSize, warning_text_spacing, ColorAlpha(BLACK, (float)warning_alpha / 255.0f));
        DrawRectangleRoundedLinesEx({warning_position.x, warning_position.y, warning_size.x, warning_size.y}, 0.5f, 0, 8.0f, ColorAlpha(BLACK, (float)warning_alpha / 255.0f));
    }
}


void Manager::Warning(std::string warning, float time, Color color) {
    warning_appeard = false;
    warning_alpha = 0;
    warning_alpha_timer = WARNING_ALPHA_TIME;
    warning_color = color;

    warning_text_fontSize = 100;
    warning_text_spacing = 8;

    warning_text = warning;
    warning_timer = time;

    warning_text_size = MeasureTextEx(*AssetManager::GetFont(AssetManager::FONT::FONT_DEFAULT_BOLD), warning_text.c_str(), warning_text_fontSize, warning_text_spacing);
    warning_size = {warning_text_size.x + 200, warning_text_size.y + 45};

    if (warning_size.x < 800) {
        warning_size.x = 800;
    }
    if (warning_size.y < 150) {
        warning_size.y = 150;
    }

    warning_position = {(float)GetScreenWidth() / 2.0f - warning_size.x / 2.0f, -30};
}