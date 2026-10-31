//
// Created by Gussi on 31.10.2026.
//

#include "../header/SearchServer.h"
#include <sstream>


std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<RelativeIndex>> result;
    std::vector <std::map<int, std::string>> dictionaryRequestVec;  // уникальный словарь для поисковых слов (слово и количество раз)
    //перебираеи по очереди каждый поисковый запрос из request.json
    for (auto &elemantVec : queries_input) {
        std::map<std::string, int> bufferMap;
        bufferMap.clear();
        // формируем уникальный словарь. Берем одну строку
        // и выделяем каждое слово
        std::string textWorld;
        std::stringstream ss{elemantVec};
        while (ss >> textWorld) {
            // если ни одного включения текста не найдена в текущий словарь,
            // то добавить это слово в словарь со значением 1
            if (bufferMap.find(textWorld) == bufferMap.end()) {
                bufferMap[textWorld] = 1;
            } else { // если слово есть, то ++
                bufferMap[textWorld]++;
            }
        }

        // создаем второй словарь, в котором будем менять местами first and second
        // т.е словарь будет отсортирован по количеству вхождений слова count
        std::map<int, std::string> changeMap;
        changeMap.clear();
        for (auto &iterParentMap : bufferMap) {
            std::pair <int, std::string> pairForChange;
            pairForChange.first = iterParentMap.second;
            pairForChange.second = iterParentMap.first;
            changeMap.insert(pairForChange);
        }
        dictionaryRequestVec.push_back(changeMap);
    }
    // Здесь имеем вектор dictionaryRequestVec в котором записано количество вхождений
    // каждого слова в поисковый запрос
    _index=
    return result;
}
