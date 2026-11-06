//
// Created by codered404 on 05.11.26.
//

#include "raylib.h"
#include "Templates.h"
#include "../Manager.h"
#include "curl/curl.h"

void Templates::LoadTemplates() {
    CURL* curl = curl_easy_init();

    if (curl) {
        std::string tempBuffer;

        curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/CodeRed404/Vocabularies/refs/heads/main/templates/template_03_11_2026.csv");

        // tell curl, where to save the loaded data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tempBuffer);

        // activate ssl for android
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

        // execute requests
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            // error while loading
            Manager::Warning("loading error 404", 5, RED);
        } else {
            // loaded successfully
            Manager::Warning("Data loaded", 3, GREEN);
        }

        curl_easy_cleanup(curl);
    }
}

size_t Templates::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* buffer = (std::string*)userp;
    buffer->append((char*)contents, totalSize);
    return totalSize;
}