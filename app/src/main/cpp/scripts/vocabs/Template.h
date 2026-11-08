//
// Created by codered404 on 05.11.26.
//

#ifndef VOCABULARY_TEMPLATE_H
#define VOCABULARY_TEMPLATE_H

#include "Vocab.h"
#include "vector"

struct Template {
    int id;
    std::string name;
    std::vector<Vocab> vocabs;
};

#endif //VOCABULARY_TEMPLATE_H
