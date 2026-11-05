//
// Created by codered404 on 03.11.26.
//

#ifndef VOCABULARY_VOCABSMENU_H
#define VOCABULARY_VOCABSMENU_H

#include "raylib.h"
#include "SceneManager.h"
#include "Scene.h"
#include "../ui/Text.h"
#include "../ui/Button.h"

class VocabsMenu : public Scene {
    public:
        enum VOCABS_MENU_MODE {
            VOCABS_MENU_EDIT,
            VOCABS_MENU_TRAIN
        };
    public:
        VocabsMenu(VOCABS_MENU_MODE mode);

        void Update(const float& delta) override;
        void Draw() override;
    private:
        VOCABS_MENU_MODE mode;

        std::unique_ptr<Text> heading;

        std::unique_ptr<Button> button_back;

        void UpdateUI(const float& delta);
        void DrawUI();
};


#endif //VOCABULARY_VOCABSMENU_H
