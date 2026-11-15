//
// Created by codered404 on 05.11.26.
//

// It's the first time I use curl, so it can have some issues or some opportunities for improvement

#include "raylib.h"
#include "Templates.h"
#include "../Manager.h"
#include "curl/curl.h"
#include <sstream>
#include <fstream>
#include "nlohmann/json.hpp"

std::vector<Template> Templates::templates;
int Templates::count;
std::string Templates::globalCaCertPath = "";

void Templates::LoadTemplatesOnline() {
    std::vector<Template> templates_backup = templates;
    templates.clear();

    CURL* curl = curl_easy_init();

    if (curl) {
        std::string tempBuffer;

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/CodeRed404/Vocabularies/contents/templates");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "CodeRed404_Agent");

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

        //curl_easy_setopt(curl, CURLOPT_CAPATH, "/system/etc/security/cacerts/");

        // execute requests
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            // error while loading
            templates = templates_backup;
            Manager::Warning("loading error 404", 3, RED);
        } else {
            // loaded successfully

            templates.clear();

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
            }
            count = templates.size();

            Manager::Warning("Data loaded", 2, GREEN);
            SaveTemplatesLocal();
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



void Templates::SaveTemplatesLocal() {
    std::ofstream o_stream;
    o_stream.open("templates.txt");

    if (!o_stream.is_open()) {
        Manager::Warning("Saving failed", 3, RED);
        return;
    }

    o_stream.clear();

    //std::vector<Template> templates_l = *Templates::GetTemplatesAddr();
    std::vector<Template> templates_l = templates;

    std::string o_tlsData = "";
    for (int i = 0; i < templates_l.size(); i++) {
        Template tl = templates_l[i];

        // line 0: tl id; line 1: tl name
        o_tlsData += std::to_string(tl.id) + "\n";
        o_tlsData += tl.name + "\n";

        for (Vocab v : tl.vocabs) {
            o_tlsData += std::to_string(v.id) + "\n";
            o_tlsData += v.en + "\n";
            o_tlsData += v.de + "\n";
        }

        o_tlsData += ">\n";




        /*
         * IGNORE
        o_tlsData += "{" + tl.name + "|" + std::to_string(tl.vocabs.size()) + "|";
        for (Vocab v : tl.vocabs) {
            o_tlsData += "[";
            o_tlsData += std::to_string(v.id) + ";" + v.en + ";" + v.de;
            o_tlsData += "]";
        }
         */
    }
    o_stream << o_tlsData;
    o_stream.close();
}

void Templates::LoadTemplatesLocal() {
    std::ifstream i_stream;
    i_stream.open("templates.txt");

    if (!i_stream.is_open()) {
        Manager::Warning("Loading saves failed", 3, RED);
        return;
    }

    std::vector<Template> templates_l;
    Template tl;
    Vocab v = Vocab();
    std::string line;
    int iotll = 0; // index of template line

    while(std::getline(i_stream, line)) {
        switch (iotll) {
            case 0:
                tl = Template();
                tl.id = std::stoi(line);
                break;
            case 1:
                tl.name = line;
                break;
            default:
                if (line == ">") {
                    templates_l.push_back(tl);
                    iotll = 0;
                    continue;
                }
                switch ((iotll + 1) % 3) {
                    case 0:
                        v.id = std::stoi(line);
                        break;
                    case 1:
                        v.en = line;
                        break;
                    case 2:
                        v.de = line;
                        tl.vocabs.push_back(v);
                        v = Vocab();
                        break;
                }
                break;
        }

        iotll++;
    }

    templates = templates_l;
    count = templates.size();

    i_stream.close();





    /*
     * IGNORE
    std::string i_tlsData = "";
    std::string tl_data = "";
    Template tl;
    int tmp_index = 0;

    i_stream >> i_tlsData;

    while(!i_tlsData.empty()) {
        int begin_tl = i_tlsData.find_first_of('{');
        int end_tl = i_tlsData.find_first_of(']');
        tl_data = i_tlsData.substr(begin_tl, end_tl);

        int vocabs_count = tl_data.substr(tl_data.find_)

        tmp_index = tl_data.find_first_of('[');
        tl.name = (0, tmp_index);
        tl_data = tl_data.substr(tmp_index, end_tl);

        tmp_index = tl_data.find_first_of(';');
        tl_data = tl_data.substr(tmp_index, end_tl);
        while ()

        i_tlsData = i_tlsData.substr(end_tl, i_tlsData.back());
    }

    i_stream.close();
     */
}