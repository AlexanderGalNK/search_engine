//
// Created by Gussi on 01.09.2026.
//

#ifndef SEARCH_ENGINE_ANSWER_H
#define SEARCH_ENGINE_ANSWER_H
#include <string>
#include "nlohmann/json.hpp"

class answerClass {
    public:
    answerClass(std::string fileNameAnswer) {
        createAnswerFile(fileNameAnswer);
    };
    void createAnswerFile(std::string fileNameAnswer);

private:
struct relevanceStr {
    std::pair <std::string, int> docid;
    std::pair <std::string, float> rank;
};

struct requestStruct {
    std::string result;
    //std::pair <std::string, bool> result;
    //std::pair <std::string, std::vector <relevanceStr>> relevance;
};
    std::pair <std::string, requestStruct> answer;
    //std::pair <std::string, std::string> answer;
};


#endif //SEARCH_ENGINE_ANSWER_H