#pragma once

#include <string>
#include <vector>
#include <map>
#include "main.h"


/**
 * @class InvertedIndex
 * Класс для построения и работы с инвертированным индексом.
 */
class InvertedIndex {
public:
    InvertedIndex() = default;

    /**
     * Обновляет базу документов и пересчитывает словарь частот.
     * @param input_docs Вектор строк с содержимым документов.
     */
    void UpdateDocumentBase(std::vector<std::string> input_docs);

    std::map<std::string, std::vector<Entry>> getTextBaseAfterParsing( );
    /**
     * Получает список документов, в которых встречается слово, и его частоту.
     * @param word Слово, для которого требуется статистика.
     * @return Вектор структур Entry, отсортированных по doc_id.
     */
    std::vector<Entry> GetWordCount(const std::string& word);

private:
    std::vector<std::string> docs; ///< Оригинальные документы
    std::map<std::string, std::vector<Entry>> freq_dictionary; ///< Частотный словарь слов
};
