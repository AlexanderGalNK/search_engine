//
// Created by Gussi on 08.09.2026.
//

#include "../header/ConverterJSON.h"

#include <fstream>
#include <iostream>
#include <exception>
#include <format>

using json =nlohmann::json;

class InvalidException : public std::exception {
public:
    // Конструктор класса прерывания
    InvalidException(const std::string & message) : msg(message)
    {}
    const char* what() const noexcept override
    {
        return msg.c_str();//"Invalid config file";
    }
    private:
    std::string msg;
};

ConverterJSON::ConverterJSON(std::string fileNameConfig) {
    openConfigFile(fileNameConfig);
    openFileRequest("requests.json");
}

void ConverterJSON::openConfigFile(std::string fileNameConfig) {
    std::ifstream config_file(fileNameConfig);
    try {
        if (config_file.is_open()) {    // if file not open -> exception
            // Парсим JSON из потока
            json data = json::parse(config_file);

            // In json has key config and files?   or  config is object-JSON (key->value)
            if (!data.contains("config") || !data["config"].is_object() ||
                !data.contains("files"))// || !data["files"].is_object())  value is array!!!
            {
                throw InvalidException("Invalid config file");
            } else
            {
                auto configObj = data["config"];
                if (configObj.contains("name")) {
                    this->_configVar.name= configObj["name"].get<std::string>();
                    std::cout << "Starting " << this->_configVar.name << std::endl;
                }

                if (configObj.contains("version"))
                    this->_configVar.version= configObj["version"].get<std::string>();
                if (configObj.contains("max_responses"))
                    this->_configVar.max_responses= configObj["max_responses"].get<int>();

                // find path to file
                const auto &configArray = data["files"];
                // в константе сохранились пути к файлам по которым нужно осуществлять поиск
                // из файла config.json
                // записываем пути в переменную-структуру vecConfigFiles с описанием файлов
                for (auto &item : configArray) {
                    oneConfigFileDescription oneVar;
                    oneVar.userPath=item.get<std::string>();
                    vecConfigFiles.push_back(oneVar);
                }
            }
        }else {
            //file config.json not open
            throw InvalidException("config file is missing");
        }
    }
    catch (const InvalidException &x)
        {
        std::cerr << x.what() << std::endl;
        }
    config_file.close();
    findTxtFile();

}

// ищем файлы по путям, указанным в config.json
void ConverterJSON::findTxtFile() {
    //Нужно сделать итерацию по вектору для проверки путей. Существуют ли по ним файлы, валидны они или нет
    for (auto &iter : vecConfigFiles) {
        auto userPath = iter.userPath.substr(iter.userPath.find("/")+1, iter.userPath.size()-iter.userPath.find("/"));
        std::ifstream findTxtFile(userPath);
        if (findTxtFile.is_open()) {
            iter.fileIsFound = true;    // file founded
            if (controlTxtFile(findTxtFile, iter)) {
                iter.goodTxtFile = true;
                if (findTxtFile.is_open())
                    findTxtFile.seekg(0 , std::ios::beg);
                std::string strBuffer = "";
                //std::getline(findTxtFile, iter.text);
                while (findTxtFile >> strBuffer) {
                    iter.text += strBuffer;
                }

            } else iter.goodTxtFile = false;
            findTxtFile.close();
        } else {
            iter.fileIsFound = false;    // file not found
        }
    }
}

// control file. Less than 1000 worlds and every worlds less than 100 characters
bool ConverterJSON::controlTxtFile(std::ifstream &userFileTxt, oneConfigFileDescription &var) {
    std::string textWorld;
    int counter = 0;
    while (userFileTxt>>textWorld) {
        counter++;
        var.text += textWorld+ " ";
        if (counter>1000) return false;
        if (textWorld.length() > 100) return false;
    }
    var.totalCountWorldInText = counter;
    return true;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    return this->_requestMessage;
}

void ConverterJSON::openFileRequest(std::string requestPath) {
    std::ifstream request_file(requestPath);
    try {
        if (request_file.is_open()) {    // if file not open -> exception
            // Парсим JSON из потока
            json data = json::parse(request_file);

            // In json has key config and files?   or  config is object-JSON (key->value)
            if (!data.contains("requests"))
            {
                throw InvalidException("Invalid request file");
            } else
            {
                // find message in file
                const auto &requestArray = data["requests"];
                _requestMessage.clear();
                for (auto &item : requestArray) {
                    _requestMessage.push_back(item.get<std::string>());
                }
            }
        }else {
            //file request.json not open
            throw InvalidException("Exception: file is missing");
        }
    }
    catch (const InvalidException &x)
    {
        std::cerr << x.what() << std::endl;
    }
    request_file.close();
    if (!controlRequestMessage()) std::cout << std::endl << "Request File Error" << std::endl;
}

bool ConverterJSON::controlRequestMessage() {
    // проверяем чтобы поле содержало не более 1000 запросов, каждый из
    // которых включает от одного до десяти слов.
    int counter = 0;
    // иттерация по вектору
    for (auto &requestMessage : _requestMessage) {
        counter++;
        if (counter>1000) return false;
        int counterWorld=0;
        std::string textWorld;
        std::stringstream ss{requestMessage};
        while (ss >> textWorld) {
            counterWorld++;
            if (counterWorld > 10) return false;
        }
    }
    return true;
}

// Объявляем to_json (должен быть в том же пространстве имён, что и типы)
void to_json(json& j, const relevanceStruct& v) {
    j["docid"] = v.docid;
    j["rank"]  = v.rank;
}

void to_json(json& j, const requestStruct& v) {
    j["result"]    = v.result;
    j["relevance"] = v.relevance;
}

void ConverterJSON::createAnswerFile(std::string fileNameAnswer,  std::vector<std::vector<RelativeIndex>> varResponse) {
    // Создаём объект ofstream и открываем файл для перезаписи
    std::ofstream outFile(fileNameAnswer);

    // Проверяем, что файл успешно открыт
    if (outFile.is_open()) {
        requestStruct requestStr;

        // словарь для хранения ответов
        answerMap answers;
        // счетчик для изменения id запроса
        int counterRequest = 1;
        for (auto &item : varResponse) {
            requestStr.requestId = std::format("request{:03}", counterRequest);
            if (item.size()) {  // Запрос не пустой
                requestStr.result = true;
                for (auto &it : item) {
                    requestStr.relevance.push_back({it.doc_id, it.rank});
                }
            } else {    // Нет совпадений по поиску rank =0
                requestStr.result = false;
            }
            // Если нужно несколько запросов, добавляем их в map
            answers[requestStr.requestId] = requestStr;
            counterRequest++;
            requestStr.relevance.clear();
        }

        json data;
        data["answers"] = answers;
        outFile << data.dump(4); // 4 — отступ для читаемости

        // Не забываем закрыть файл
        outFile.close();
    } else {
        std::cerr << "Не удалось открыть файл для записи!\n";
    }

}
/*
void ConverterJSON::getTextBaseAfterParsing(std::map<std::string, std::vector<Entry>> var) {
    // Полностью очищаем словарь с потенциальным освобождением памяти
    std::map<std::string, std::vector<Entry>>().swap(freq_dictionary);
    // Записываем новые данные в словарь ConverterJSON
    for (auto &item : var) {
        this->freq_dictionary.insert(std::pair<std::string, std::vector<Entry>>(item.first, item.second));//std::vector<Entry>()));
    }
}
*/

int ConverterJSON::GetResponsesLimit() {
    return _configVar.max_responses;
}


// Метод возвращает вектор текстов из фалов
//т.е. тексты самих файлов из config.json
std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> textDocuments;
    textDocuments.clear();
    for (auto &doc : vecConfigFiles) {
        textDocuments.push_back(doc.text);
    }
    return textDocuments;
}
