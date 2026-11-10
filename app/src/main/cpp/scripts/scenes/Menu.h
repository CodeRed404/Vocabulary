//
// Created by codered404 on 01.11.26.
//

#ifndef VOCABULARY_MENU_H
#define VOCABULARY_MENU_H

#include "Scene.h"
#include "../Global.h"
#include "SceneManager.h"
#include "SettingsMenu.h"
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

        bool robot_is_texture_0;
        bool robot_goes_to_right;
        float robot_texture_switch_timer;
        float robot_texture_switch_time;
        float robot_x_pos;
        float robot_y_pos;
        float robot_speed;

        std::unique_ptr<Text> heading;
        std::unique_ptr<Text> developer_credit;

        std::unique_ptr<Button> button_settings;
        std::unique_ptr<Button> button_train;
        std::unique_ptr<Button> button_vocabs;
        std::unique_ptr<Button> button_quit;

        void UpdateUI(const float& delta);
        void DrawUI();
};


#endif //VOCABULARY_MENU_H
