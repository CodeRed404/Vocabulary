//
// Created by codered404 on 10.11.26.
//

#ifndef VOCABULARY_SETTINGSMENU_H
#define VOCABULARY_SETTINGSMENU_H

#include "raylib.h"
#include "Scene.h"
#include "../ui/Button.h"

class SettingsMenu : public Scene {
    public:
        SettingsMenu();

        void Update(const float& delta) override;
        void Draw() override;
    private:
        std::unique_ptr<Text> heading;

        std::unique_ptr<Button> button_inv_sync_templates; // inv = invisible
        std::unique_ptr<Button> button_back;

        void UpdateUI(const float& delta);
        void DrawUI();

        void SyncTemplates(const float& delta);
};


#endif //VOCABULARY_SETTINGSMENU_H
