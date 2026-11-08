#include <string>
#include <iostream>
#include <conio.h> // для getch()

#include "header/ConverterJSON.h"
#include "header/InvertedIndex.h"
#include "header/SearchServer.h"

int main() {
    // класс для работы с JSON объектами
    ConverterJSON configFileVar("config.json");

    // создаем класс для ранжирования документов
    InvertedIndex varInvertedIndex;
    //Обновляем базу, которая парсит текстовые документы из Config.json
    varInvertedIndex.UpdateDocumentBase(configFileVar.GetTextDocuments());

    // В базе появляется все слова, для которых указывается где (в каком тексте)
    // и сколько раз они в этом тексте встречались.
    SearchServer RelevanteBase(varInvertedIndex);

    // Создаем файл с ответами на поисковые запросы
    configFileVar.createAnswerFile("answers.json", RelevanteBase.search(configFileVar.GetRequests()));

}
