//
// Created by codered404 on 03.11.26.
//

#ifndef VOCABULARY_TEMPLATESMENU_H
#define VOCABULARY_TEMPLATESMENU_H

#include "raylib.h"
#include "SceneManager.h"
#include "Scene.h"
#include "../ui/Text.h"
#include "../ui/Button.h"

class TemplatesMenu : public Scene {
    public:
        TemplatesMenu();

        void Update(const float& delta) override;
        void Draw() override;
    private:
        std::unique_ptr<Text> heading;

        std::unique_ptr<Button> button_back;

        void UpdateUI(const float& delta);
        void DrawUI();
};


#endif //VOCABULARY_TEMPLATESMENU_H
