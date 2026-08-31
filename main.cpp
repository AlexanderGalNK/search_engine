#include <iostream>
#include <string>
#include <fstream>

#include "header/configClass.h"
#include "nlohmann/json.hpp"

int main() {
    configClass configFile("configUser.json");
    //configFile.openFileConfig("configUser.json");

}