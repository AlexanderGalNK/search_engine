//
// Created by Gussi on 28.08.2026.
//

#include "../header/requestClass.h"
#include <fstream>
#include <iostream>
using json =nlohmann::json;

class InvalidRequestException : public std::exception {
public:
    // Конструктор класса прерывания
    InvalidRequestException(const std::string & message) : msg(message)
    {}
    const char* what() const noexcept override
    {
        return msg.c_str();//"Exception message";
    }
private:
    std::string msg;
};

void requestClass::openFileRequest(std::string requestPath) {
    std::ifstream request_file(requestPath);
    try {
        if (request_file.is_open()) {    // if file not open -> exception
            // Парсим JSON из потока
            json data = json::parse(request_file);

            // In json has key config and files?   or  config is object-JSON (key->value)
            if (!data.contains("requests"))
            {
                throw InvalidRequestException("Invalid request file");
            } else
            {
                // find message in file
                const auto &requestArray = data["requests"];
                for (auto &item : requestArray) {
                    _requestMessage.push_back(item.get<std::string>());
                }
            }
        }else {
            //file request.json not open
            throw InvalidRequestException("Exception file is missing");
        }
    }
    catch (const InvalidRequestException &x)
    {
        std::cerr << x.what() << std::endl;
    }
    request_file.close();
    if (!controlRequestMessage()) std::cout << std::endl << "Request File Error" << std::endl;
}

bool requestClass::controlRequestMessage() {
    // проверяем чтобы поле содержало не более 1000 запросов, каждый из
    // которых включает от одного до десяти слов.
    int counter = 0;
    // иттерация по вектору
    for (auto &requestMessage : _requestMessage) {
        counter++;
        if (counter>1000) return false;

        int counterWorld=0;
        std::string textWorld;
        std::stringstream ss{requestMessage};
        while (ss >> textWorld) {
            counterWorld++;
            if (counterWorld > 10) return false;
        }
    }
    return true;
}



