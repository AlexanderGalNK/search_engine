#include <iostream>
#include <string>
#include <fstream>

#include "header/ConverterJSON.h"
#include "header/InvertedIndex.h"
#include "header/SearchServer.h"

#include "nlohmann/json.hpp"

int main() {
    // класс для работы с JSON объектами
    ConverterJSON configFileVar("configUser.json");

    // создаем класс для ранжирования документов
    InvertedIndex varInvertedIndex;
    //Обновляем базу, которая парсит текстовые документы из Config.json
    varInvertedIndex.UpdateDocumentBase(configFileVar.GetTextDocuments());


    // В базе появляется все слова, для которых указывается где (в каком тексте)
    // и сколько раз они в этом тексте встречались.
    SearchServer RelevanteBase(varInvertedIndex);
//    RelevanteBase.search(configFileVar.GetRequests());



    // Создаем файл с ответами на поисковые запросы
    std::vector<std::vector<RelativeIndex>> buffer = RelevanteBase.search(configFileVar.GetRequests());
    configFileVar.createAnswerFile("answers.json", RelevanteBase.search(configFileVar.GetRequests()));
    //std::vector<Entry> countFind = varInvertedIndex.GetWordCount("after");

}
