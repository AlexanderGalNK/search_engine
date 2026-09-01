#include <iostream>
#include <string>
#include <fstream>

#include "header/answer.h"
#include "header/configClass.h"
#include "header/requestClass.h"
#include "nlohmann/json.hpp"

int main() {
    configClass configFileVar("configUser.json");
    requestClass requestFileVar("requests.json");
    answerClass answerFileVar("answers.json");
}