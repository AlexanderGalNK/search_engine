//
// Created by Gussi on 20.08.2026.
//

#ifndef SEARCH_ENGINE_CONFIGCLASS_H
#define SEARCH_ENGINE_CONFIGCLASS_H
#include <string>
#include "nlohmann/json.hpp"


class configClass {
public:
    configClass(std::string fileNameConfig) {
    openFileConfig(fileNameConfig);
    };
    void openFileConfig(std::string fileNameConfig);
    void printConfig();
    //~configClass() {    };

private:
    struct configVar {
        std::string name;
        std::string version;
        int max_responses;
    } _configVar;

/*    struct configFile {
        std::string name;

    };
    */
};


#endif //SEARCH_ENGINE_CONFIGCLASS_H