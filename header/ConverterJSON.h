//
// Created by Gussi on 08.09.2026.
//

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H
#include <string>
#include "nlohmann/json.hpp"
#include "main.h"

// struct for answer
struct relevanceStruct {
    size_t docid;
    float rank;
};

struct requestStruct {
    std::string requestId;
    bool result;
    std::vector <relevanceStruct> relevance;
};

using answerMap = std::map<std::string, requestStruct>;

/**
*Класс для работы с JSON-файлами
*/
class ConverterJSON {
private:
    /*
     *Структура для общего описания поискового движка
     */
    struct configVar {
        std::string name;
        std::string version;
        int max_responses;
    } _configVar;

    /*
     *Описание текстового файла по указанному адресу
     * путь
     * сам текст
     * получилось ли найти и открыть файл
     * файл менее 1000 слов и все слова менее 100 символов
     */
    struct oneTXTFileDescription {
        std::string userPath;
        std::string text;
        bool fileIsFound;       // true - found
        bool goodTxtFile;       // true - file less then 1000 charecters and less than 100 cheracters in the word
    };
    // список файлов из файла config.json c проверками
    std::vector<oneTXTFileDescription> vecConfigFiles;
    // список запросов из request.json
    std::vector<std::string> _requestMessage;
    // Частотный словарь слов в документах
    std::map<std::string, std::vector<Entry>> freq_dictionary;

public:
    ConverterJSON()=default;    // генерация конструктора по умолчанию
    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    std::vector<std::string> GetTextDocuments();

    /**
    * Конструктор класса.
    * @param Принимает на вход имя файла, в котором идут настройки
    * для поиска.
    */
    ConverterJSON(std::string fileNameConfig);;
    // ищем файлы по путям, указанным в config.json
    void openConfigFile(std::string fileNameConfig);
    // ищем файлы по путям, указанным в config.json
    void findTxtFile();
    // control file. Less than 1000 worlds and every worlds less than 100 characters
    // применять в паре с полем goodTxtFile
    bool controlTxtFile(std::ifstream &userFileTxt, oneTXTFileDescription &var);

    // методы для работы с Request.json
    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    std::vector<std::string>GetRequests();
    /*
     * Открываем файл Request.json для считывания запросов
     * @param имя файла JSON для открытия
     */
    void openFileRequest(std::string fileRequest);
    // проверяем чтобы поле содержало не более 1000 запросов, каждый из
    // которых включает от одного до десяти слов.
    bool controlRequestMessage();


    /*
     * Методы для генерации ответа answer,
     * @param имя JSON файла для создания/перезаписи. Куда будет сохранятся результат - ответ
     *        вектор, в который передает релевантность документов для ее записи в ответ.
     */
    void createAnswerFile(std::string fileNameAnswer, std::vector<std::vector<RelativeIndex>> );
    /**
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return
    */
    int GetResponsesLimit();
};


#endif //SEARCH_ENGINE_CONVERTERJSON_H