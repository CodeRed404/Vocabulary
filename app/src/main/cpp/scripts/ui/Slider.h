//
// Created by codered404 on 11.11.26.
//

#ifndef VOCABULARY_SLIDER_H
#define VOCABULARY_SLIDER_H

#include "UI.h"

class Slider : public UI {
    public:
        Slider();

        void Update(const float& delta) override;
        void Draw() override;
};


#endif //VOCABULARY_SLIDER_H
