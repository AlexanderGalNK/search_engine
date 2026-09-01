//
// Created by Gussi on 01.09.2026.
//

#include "../header/answer.h"
#include <fstream>
#include <iostream>
using json =nlohmann::json;

void answerClass::createAnswerFile(std::string fileNameAnswer) {
    // Создаём объект ofstream и открываем файл для перезаписи
    std::ofstream outFile(fileNameAnswer);

    // Проверяем, что файл успешно открыт
    if (outFile.is_open()) {
        this->answer.first = "request001";
        this->answer.second.result = "123";
        //this->answer.second.result.second = true;

        json data;
        data["answer"] = json::object();
        //json &answer = data["answer"];


        // Дописываем данные
        outFile << data;
        // Не забываем закрыть файл
        outFile.close();
    } else {
        std::cerr << "Не удалось открыть файл для записи!\n";
    }
}
/*
{
    "answers": {
        "request001": {
            "result": "true",
            "relevance": [
            { "docid": 0, "rank": 0.989 },
            { "docid": 1, "rank": 0.897 },
            { "docid": 2, "rank": 0.750 }
            ]
            },
            "request002": {
                "result": "true",
                "relevance": [
                { "docid": 0, "rank": 0.769 }
                ]
                },
                "request003": {
                    "result": "false"
                    }
    }
    */