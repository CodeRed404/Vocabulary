//
// Created by codered404 on 15.11.26.
//

#ifndef VOCABULARY_UI_H
#define VOCABULARY_UI_H

class UI {
    public:
        virtual void Update(const float& delta) {}
        virtual void Draw() {}
    protected:
        UI() {}
};

#endif //VOCABULARY_UI_H
