#include "ConfigParser.h"
#include <fstream>
#include <iostream>

nlohmann::json ConfigParser::parse(const std::string& filePath) {
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        throw std::runtime_error("Could not open config file: " + filePath);
    }

    nlohmann::json config;
    
    try {
        file >> config;  
    } catch (const std::exception& e) {
        std::cerr << "[ConfigParser] Error parsing JSON: " << e.what() << std::endl;
        throw;  
    }

    return config;
}
