//
// Created by codered404 on 08.11.26.
//

#ifndef VOCABULARY_TRAINSCENE_H
#define VOCABULARY_TRAINSCENE_H

#include "Template.h"
#include "../scenes/Scene.h"
#include "../ui/Button.h"

class TrainScene : public Scene {
    public:
        TrainScene(Template* template_ptr);
        void Update(const float& delta) override;
        void Draw() override;
    private:
        Template* template_ptr;

        bool help_info = false;

        std::unique_ptr<Button> button_list_vocabs;
        std::unique_ptr<Button> button_back;
};


#endif //VOCABULARY_TRAINSCENE_H
