//
// Created by codered404 on 03.11.26.
//

#ifndef VOCABULARY_TRAINMENU_H
#define VOCABULARY_TRAINMENU_H

#include "raylib.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TemplatesMenu.h"
#include "VocabsMenu.h"
#include "../ui/Text.h"
#include "../ui/Button.h"

class TrainMenu : public Scene {
    public:
        TrainMenu();

        void Update(const float& delta) override;
        void Draw() override;
    private:
        std::unique_ptr<Text> heading;

        std::unique_ptr<Button> button_templates_menu;
        std::unique_ptr<Button> button_userVocabs_menu;
        std::unique_ptr<Button> button_back;

        void UpdateUI(const float& delta);
        void DrawUI();
};


#endif //VOCABULARY_TRAINMENU_H
