//
// Created by Gussi on 20.08.2026.
//

#include "../header/configClass.h"
#include <fstream>
#include <iostream>
#include <exception>
using json =nlohmann::json;

class InvalidConfigException : public std::exception {
public:
    // Конструктор класса прерывания
    InvalidConfigException(const std::string & message) : msg(message)
    {}
    const char* what() const noexcept override
    {
        return msg.c_str();//"Invalid config file";
    }
    private:
    std::string msg;
};

void configClass::openConfigFile(std::string fileNameConfig) {
    std::ifstream config_file(fileNameConfig);
    try {
        if (config_file.is_open()) {    // if file not open -> exception
            // Парсим JSON из потока
            json data = json::parse(config_file);

            // In json has key config and files?   or  config is object-JSON (key->value)
            if (!data.contains("config") || !data["config"].is_object() ||
                !data.contains("files"))// || !data["files"].is_object())  value is array!!!
            {
                throw InvalidConfigException("Invalid config file");
            } else
            {
                auto configObj = data["config"];
                if (configObj.contains("name")) {
                    this->_configVar.name= configObj["name"].get<std::string>();
                    std::cout << "Starting " << this->_configVar.name << std::endl;
                }

                if (configObj.contains("version"))
                    this->_configVar.version= configObj["version"].get<std::string>();
                if (configObj.contains("max_responses"))
                    this->_configVar.max_responses= configObj["max_responses"].get<int>();

                // find path to file
                const auto &configArray = data["files"];
                for (auto &item : configArray) {
                    _configFiles.push_back(item.get<std::string>());
                }
            }
        }else {
            //file config.json not open
            throw InvalidConfigException("config file is missing");
        }
    }
    catch (const InvalidConfigException &x)
        {
        std::cerr << x.what() << std::endl;
        }
    config_file.close();
    findTxtFile();
}

void configClass::findTxtFile() {
    // ищем файлы по путям, указанным в config.json
    for (auto &iter : this->_configFiles) {
        auto userPath = iter.substr(iter.find("/")+1, iter.size()-iter.find("/"));
        std::ifstream findTxtFile(userPath);
        if (findTxtFile.is_open()) {
            //std::cout << iter << " found" << std::endl;
            if (controlTxtFile(findTxtFile)) {
                //std::cout << iter << " good file" << std::endl;
            } else std::cout << iter << " bad file" << std::endl;
        } else {
            std::cout << iter << " not found" << std::endl;
        }
        findTxtFile.close();
    }
}

// control file. Less than 1000 worlds and every worlds less than 100 characters
bool configClass::controlTxtFile(std::ifstream &userFileTxt) {
    std::string textWorld;
    int counter = 0;
    while (userFileTxt>>textWorld) {
        counter++;
        if (counter>1000) return false;
        if (textWorld.length() > 100) return false;
    }
    return true;
}


