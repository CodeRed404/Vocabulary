//
// Created by codered404 on 05.11.26.
//

#ifndef VOCABULARY_TEMPLATES_H
#define VOCABULARY_TEMPLATES_H

#include "Template.h"
#include "vector"

class Templates {
    public:
        static void LoadTemplates();
    private:
        static std::vector<Template> templates;

        static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};


#endif //VOCABULARY_TEMPLATES_H
