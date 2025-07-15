#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>
#include "../external/json/json.hpp"


class ConfigParser {
public:
    static nlohmann::json parse(const std::string& filePath);
};

#endif 
