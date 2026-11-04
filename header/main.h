//
// Created by Gussi on 14.10.2026.
//

#ifndef SEARCH_ENGINE_MAIN_H
#define SEARCH_ENGINE_MAIN_H
#include <string>

/**
 * @struct Entry
 * Структура, описывающая частоту слова в конкретном документе
 */
struct Entry {
    size_t doc_id;  ///< ID документа
    size_t count;   ///< Количество вхождений слова в документ

    bool operator==(const Entry& other) const {
        return doc_id == other.doc_id && count == other.count;
    }
};

struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator==(const RelativeIndex &other) const
    {return(doc_id== other.doc_id&&rank==other.rank);
    }
};

#endif //SEARCH_ENGINE_MAIN_H