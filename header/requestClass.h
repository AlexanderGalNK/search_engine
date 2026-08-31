//
// Created by Gussi on 28.08.2026.
//

#ifndef SEARCH_ENGINE_REQUESTCLASS_H
#define SEARCH_ENGINE_REQUESTCLASS_H
#include <string>
#include "nlohmann/json.hpp"

class requestClass {
public:
    requestClass(std::string fileRequest) {
        openFileRequest(fileRequest);
    };
    void openFileRequest(std::string requestClass);

private:
    std::vector<std::string> request;

};


#endif //SEARCH_ENGINE_REQUESTCLASS_H