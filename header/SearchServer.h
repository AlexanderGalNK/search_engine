//
// Created by Gussi on 31.10.2026.
//

#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H

#include "../header/InvertedIndex.h"

class SearchServer {
    public:
    /**
    * @param idx в конструктор класса передаётся ссылка на класс InvertedIndex,
    * чтобы SearchServer мог узнать частоту слов встречаемых в запросе
    */
    SearchServer(InvertedIndex &idx) : _index(idx) {   };

    /**
    * Метод обработки поисковых запросов
    * @param queries_input поисковые запросы взятые из файла requests.json
    * @return возвращает отсортированный список релевантных ответов для заданных запросов
    */
    std::vector<std::vector<RelativeIndex>>search(const std::vector<std::string>& queries_input);

private:

    InvertedIndex _index;
};


#endif //SEARCH_ENGINE_SEARCHSERVER_H