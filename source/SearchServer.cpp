//
// Created by Gussi on 31.10.2026.
//

#include "../header/SearchServer.h"
#include <sstream>


std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<RelativeIndex>> result;
    std::vector <std::vector <std::pair<std::string, int>>> dictionaryRequestVec;  // уникальный словарь для поисковых слов (слово и количество раз)
    //перебираеи по очереди каждый поисковый запрос из request.json
    for (auto &elemantVec : queries_input) {
        std::vector <std::pair<std::string, int>> bufferMap;
    //    std::unordered_map<std::string, int> bufferMap;
        bufferMap.clear();
        // формируем уникальный вектор. Берем одну строку
        // и выделяем каждое слово
        std::string textWorld;
        std::stringstream ss{elemantVec};
        while (ss >> textWorld) {
            // если ни одного включения текста не найдена в текущий вектор,
            // то добавить это слово в вектор со значением 1
            bool found = false;
            for (auto& p : bufferMap) {
                if (p.first == textWorld) {
                    p.second++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                bufferMap.emplace_back(textWorld, 1);  // или push_back(std::make_pair(...))
            }
        }

        // сортировка по количеству одинаковых слов в запросе
         for (auto &iterParentMap : bufferMap) {
            for (auto &iterChild : bufferMap) {
                if (iterParentMap.second < iterChild.second) {
                    iterParentMap.swap(iterChild);
                }
            }
        }
        dictionaryRequestVec.push_back(bufferMap);
    }
    // Здесь имеем вектор dictionaryRequestVec в котором записано количество вхождений
    // каждого слова в поисковый запрос

    // составляем ранг документа по соответствию поисковому запросу.

    // ложим в вектор строчку запроса из request.json
    for (auto &oneRequestVecJSON : dictionaryRequestVec) {
        std::vector <std::pair<std::string, int>> oneRequestFromJSON ;
        oneRequestFromJSON.clear();
        for (auto &elemantVec : oneRequestVecJSON){     //dictionaryRequestVec[0]) {
            oneRequestFromJSON.push_back(elemantVec);
        }

        std::vector <RelativeIndex> curRankOneRequest;
        curRankOneRequest.clear();
        // берем по одному слову из общего словаря
        // где записаны все тексты freq_request
        for (auto &dictionary : _index.getTextBaseAfterParsing()) {
            for (auto &oneWorldRequest : oneRequestFromJSON) {
                if (oneWorldRequest.first == dictionary.first) {        // сравнили слова. Они совпадают
                    // подготавливаемся к подсчету ранга
                    // копируем текущие doc_id and rank для выбранного слова
                    for (auto &oneCoincidence : dictionary.second) {
                        // Если текущий вектор не вмещает все совпадения (например слово найдено в 2-х текстах),
                        // то расширить вектор
                        while (curRankOneRequest.size() <= oneCoincidence.doc_id) {
                            curRankOneRequest.push_back({0,0});
                        }
                        curRankOneRequest[oneCoincidence.doc_id].rank += oneCoincidence.count;
                        curRankOneRequest[oneCoincidence.doc_id].doc_id = oneCoincidence.doc_id;
                    }
                }
            }
        }
        // если rank=0, то удалить строчку из вектора
        for (int i=curRankOneRequest.size()-1; i >= 0; i--) {
            if (curRankOneRequest[i].rank == 0)
                curRankOneRequest.erase(curRankOneRequest.begin() + i);
        }

        // упорядочиваем информацию в порядке снижения релевантности (rank)
        for (int i=0; i < curRankOneRequest.size(); i++) {
            for (int j=0; j < curRankOneRequest.size(); j++) {
                if (curRankOneRequest[j].rank < curRankOneRequest[j+1].rank) {
                    std::swap(curRankOneRequest[j].doc_id,  (curRankOneRequest[j+1].doc_id));
                    std::swap(curRankOneRequest[j].rank,  (curRankOneRequest[j+1].rank));
                }
            }
        }
        // Ищем абсолютную максимальную релевантность по запросу
        int maxRank = 0;
        for (auto &findMaxRanK : curRankOneRequest) {
            if (findMaxRanK.rank > maxRank)
                maxRank = findMaxRanK.rank;
        }
        //Расчитываем относительную релевантность по формуле = rank/ абсолютную максимальную релевантность
        for (auto &oneElement : curRankOneRequest) {
            oneElement.rank /= maxRank ;
        }

        while (curRankOneRequest.size() > 5) {  // max_responses from ConverterJSON.GetResponsesLimit
            curRankOneRequest.pop_back();
        }
        result.push_back(curRankOneRequest);
    }


    return result;
}
