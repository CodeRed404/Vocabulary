//
// Created by codered404 on 05.11.26.
//

#ifndef VOCABULARY_TEMPLATES_H
#define VOCABULARY_TEMPLATES_H

#include "Template.h"
#include "Vocab.h"
#include "vector"

class Templates {
    public:
        static std::string globalCaCertPath;

        static void LoadTemplates();
        static int Count();
        static std::vector<Template> *GetTemplatesAddr();
    private:
        static std::vector<Template> templates;
        static int count;

        static std::vector<Vocab> LoadVocabs(std::string templateDownloadLink);
        static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};


#endif //VOCABULARY_TEMPLATES_H
