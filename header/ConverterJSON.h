//
// Created by Gussi on 08.09.2026.
//

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H
#include <string>
#include "nlohmann/json.hpp"
#include "main.h"
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


    struct oneConfigFileDescription {
        std::string userPath;
        bool controlTxtFile(std::ifstream &userFileTxt);
        std::string text;
        bool fileIsFound;       // true - found
        bool goodTxtFile;       // true - file less then 1000 charecters and less than 100 cheracters in the word
        int32_t totalCountWorldInText;
    };
    // список файлов из файла config.json c проверками
    std::vector<oneConfigFileDescription> vecConfigFiles;
    // список запросов из request.json
    std::vector<std::string> _requestMessage;

    std::map<std::string, std::vector<Entry>> freq_dictionary; ///< Частотный словарь слов в документах



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
    void findTxtFile();
    bool controlTxtFile(std::ifstream &userFileTxt, oneConfigFileDescription &var);

    // методы для работы с Request.json
    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    std::vector<std::string>GetRequests();
    void openFileRequest(std::string fileRequest);
    bool controlRequestMessage();


    // metod for work answer
    void createAnswerFile(std::string fileNameAnswer);
    /*
     *Метод для оценки поискового выражения из request.json
     * @param requestMes какой текст искать (из файла request.json),
     *        &var.text  передаются по ссылке сами тексты
     * Метод заполняет ответ на поиск в поле requestStruct
     */
    void findRequestInFile(std::string requestMes, requestStruct &var);
    /*
     * Метод подсчета текущей релевантности
     * @param получает текст для поиска и номер поискового файла
     * return число рейтинг из расчета TF= (n/k), где n- встречаемость
     * поискового текста (сколько раз), k - общее количество слов
     */
    float calculRank(std::string textForSearch, int docidSearch);
    void getTextBaseAfterParsing(std::map<std::string, std::vector<Entry>> var);

    /*
     *Метод для сортировки файлов docid по рангу rank
     * @param requestStruct описывающий ответ на запрос
     */
    void sortRequest(requestStruct &requestStr);

    // Изучаю тестирование при помощи GoogleTest
    // Пробный метод
    int blablaTest(int arg1);

};


#endif //SEARCH_ENGINE_CONVERTERJSON_H