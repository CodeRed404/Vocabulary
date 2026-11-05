//
// Created by codered404 on 04.11.26.
//

#include "Global.h"
#include "httplib.h"
#include "fstream"
#include "iostream"

void Global::LoadTemplates() {/*
    httplib::Client cli("https://api.github.com");


    // User-Agent for GitHub
    httplib::Headers headers = {
            {"User-Agent", "Vocabulary-Program"}
    };

    httplib::Result res = cli.Get("/repos/CodeRed404/Vocabularies/contents/templates", headers);*/

    std::ofstream file;
    file.open("test.txt");

    if (GetTouchPointCount() > 0) {
        file << "hallo";
    }

    //Global::text = file.iword(0);

    file.close();

    /*
    if (res && res->status == 200) {
        std::string jsonAnswer = res->body;
    }

    /
    std::ifstream myFile("text.txt");
    std::string line;
    getline(myFile, line);
    Global::text = line;
    if (myFile.is_open()) {
        Global::text = "opened";
    }
    Global::text = "opened";
    myFile.close();
     */
}