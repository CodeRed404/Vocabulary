//
// Created by codered404 on 05.11.26.
//

#include "raylib.h"
#include "Templates.h"
#include "../Manager.h"
#include "curl/curl.h"
#include "sstream"
#include "nlohmann/json.hpp"

std::vector<Template> Templates::templates;
int Templates::count;
std::string Templates::globalCaCertPath = "";

void Templates::LoadTemplates() {
    //for (int i = 0; i < 99999999999; i++);
    CURL* curl = curl_easy_init();

    if (curl) {
        std::string tempBuffer;

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/CodeRed404/Vocabularies/contents/templates");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "CodeRed404_Agent");

        // https://raw.githubusercontent.com/CodeRed404/Vocabularies/refs/heads/main/templates/template_03_11_2026.csv



        // tell curl, where to save the loaded data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tempBuffer);

        // allow redirects
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // certificate path
        //curl_easy_setopt(curl, CURLOPT_CAINFO, globalCaCertPath.c_str());

        // activate ssl for android
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_CAPATH, "/system/etc/security/cacerts/");

        // execute requests
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            // error while loading
            Manager::Warning("loading error 404", 3, RED);
        } else {
            // loaded successfully

            nlohmann::json j = nlohmann::json::parse(tempBuffer);

            int tlID = 0;
            for (int i = 0; i < j.size(); i++, tlID++) {
                Template tl;

                tl.id = tlID;
                std::string nameText = j[i]["name"];
                tl.name = nameText.substr(0, nameText.find("."));

                tl.vocabs = LoadVocabs(j[i]["download_url"]);

                if (tl.vocabs[0].id != -1) {
                    templates.push_back(tl);
                } else {
                    Manager::Warning("tl error, maybe restart", 5, ORANGE);
                    tlID--;
                }

                count++;
            }

            Manager::Warning("Data loaded", 2, GREEN);
        }
        curl_easy_cleanup(curl);
    }

    Global::isLoading = false;
}

std::vector<Vocab> Templates::LoadVocabs(std::string templateDownloadLink) {
    CURL* curl = curl_easy_init();

    if (curl) {
        std::string tempBuffer;

        curl_easy_setopt(curl, CURLOPT_URL, templateDownloadLink.c_str());



        // tell curl, where to save the loaded data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tempBuffer);

        // allow redirects
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // certificate path
        //curl_easy_setopt(curl, CURLOPT_CAINFO, globalCaCertPath.c_str());

        // activate ssl for android
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_CAPATH, "/system/etc/security/cacerts/");

        // execute requests
        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            // successfully loaded template

            std::string line;
            std::istringstream stream(tempBuffer);

            std::vector<Vocab> vocabs;

            while (std::getline(stream, line)) {
                Vocab vocab;

                if (line == "id;en;de" || line.empty()) {
                    continue;
                }

                vocab.id = std::stoi(line.substr(0, line.find(";")));

                line = line.substr(line.find(";") + 1, line.length());

                vocab.en = line.substr(0, line.find(";"));

                line = line.substr(line.find(";") + 1, line.length());

                vocab.de = line.substr(0, line.length());

                vocabs.push_back(vocab);
            }

            curl_easy_cleanup(curl);
            return vocabs;
        }
        // error while loading template

        curl_easy_cleanup(curl);
    }

    std::vector<Vocab> errorVocabs;
    errorVocabs.push_back(Vocab());
    errorVocabs[0].id = -1;
    return errorVocabs;
}

size_t Templates::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* buffer = (std::string*)userp;
    buffer->append((char*)contents, totalSize);
    return totalSize;
}

int Templates::Count() {
    return count;
}

std::vector<Template> *Templates::GetTemplatesAddr() {
    return &templates;
}