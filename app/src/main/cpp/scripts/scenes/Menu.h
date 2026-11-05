//
// Created by codered404 on 01.11.26.
//

#ifndef VOCABULARY_MENU_H
#define VOCABULARY_MENU_H

#include "Scene.h"
#include "../Global.h"
#include "SceneManager.h"
#include "TrainMenu.h"
#include "VocabsMenu.h"
#include "../ui/Text.h"
#include "../ui/Button.h"

class Menu : public Scene {
    public:
        Menu();

        void Update(const float& delta) override;
        void Draw() override;
    private:
        bool want_to_quit;

        std::unique_ptr<Text> heading;
        std::unique_ptr<Text> developer_credit;

        std::unique_ptr<Button> button_train;
        std::unique_ptr<Button> button_vocabs;
        std::unique_ptr<Button> button_quit;

        void UpdateUI(const float& delta);
        void DrawUI();
};


#endif //VOCABULARY_MENU_H
