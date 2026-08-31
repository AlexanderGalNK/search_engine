//
// Created by Gussi on 20.08.2026.
//

#include "../header/configClass.h"
#include <fstream>
#include <sstream>
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

void configClass::openFileConfig(std::string fileNameConfig) {
    std::ifstream config_file(fileNameConfig);
    try {
        if (config_file.is_open()) {    // if file not open -> exception
            // Парсим JSON из потока
            json data = json::parse(config_file);

            // In json has key config?   or  config is object-JSON (key->value)
            if (!data.contains("config") || !data["config"].is_object())
            {
                throw InvalidConfigException("Invalid config file");
            } else
            {
                const auto configObj = data["config"];
                if (configObj.contains("name")) {
                    this->_configVar.name= configObj["name"].get<std::string>();
                    std::cout << "Starting " << this->_configVar.name << std::endl;
                }

                if (configObj.contains("version"))
                    this->_configVar.version= configObj["version"].get<std::string>();
                if (configObj.contains("max_responses"))
                    this->_configVar.max_responses= configObj["max_responses"].get<int>();
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
}
