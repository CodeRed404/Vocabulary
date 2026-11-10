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

        // train
        Vocab currVocab;
        Text currVocabIDText;
        Text currVocabText;
        float defaultVocabFontSize;
        Text tapText;
        uint8_t tapAlpha;
        bool tapUp;
        bool EN_to_DE;
        std::unique_ptr<Button> button_switchLanguage;
        // card
        bool currWordIsEN;
        Vector2 cardSize;
        Rectangle cardRect;
        std::unique_ptr<Button> cardButton; // invisible (only for IsPressed() - (can be improved))
        // not in the card
        std::unique_ptr<Button> button_random;
        std::unique_ptr<Button> button_previous;
        std::unique_ptr<Button> button_next;
        std::unique_ptr<Button> button_first;

        std::unique_ptr<Button> button_list_vocabs;
        std::unique_ptr<Button> button_back;

        void UpdateCard(const float& delta);
};


#endif //VOCABULARY_TRAINSCENE_H
