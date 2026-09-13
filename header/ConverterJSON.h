//
// Created by Gussi on 08.09.2026.
//

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H
#include <string>
#include "nlohmann/json.hpp"
#include <format>

/**
*Класс для работы с JSON-файлами
*/
// struct for answer
struct relevanceStruct {
    int docid;
    float rank;
};

struct requestStruct {
    std::string requestId;
    bool result;
    std::vector <relevanceStruct> relevance;
};

using answerMap = std::map<std::string, requestStruct>;

class ConverterJSON {
private:
    struct configVar {
        std::string name;
        std::string version;
        int max_responses;
    } _configVar;

    //std::vector<std::string> _requestMessage;
    struct oneConfigFileDescription {
        std::string userPath;
        bool controlTxtFile(std::ifstream &userFileTxt);
        std::string text;
        bool fileIsFound;       // true - found
        bool goodTxtFile;       // true - file less then 1000 charecters and less than 100 cheracters in the word
    };
    // список файлов из файла config.json c проверками
    std::vector<oneConfigFileDescription> vecConfigFiles;
    //
    std::vector<std::string> _requestMessage;



public:
    ConverterJSON()=default;    // генерация конструктора по умолчанию

    std::vector<std::string> GetTextDocuments();
    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    ConverterJSON(std::string fileNameConfig);;
    void openConfigFile(std::string fileNameConfig);
    // ищем файлы по путям, указанным в config.json
    void findTxtFile();
    bool controlTxtFile(std::ifstream &userFileTxt, oneConfigFileDescription &var);

    // методы для работы с Request.json
    void openFileRequest(std::string fileRequest);
    bool controlRequestMessage();

    // metod for work answer
    void createAnswerFile(std::string fileNameAnswer);
    void findRequestInFile(std::string requestMes, requestStruct &var);


    /**
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return
    */


};


#endif //SEARCH_ENGINE_CONVERTERJSON_H