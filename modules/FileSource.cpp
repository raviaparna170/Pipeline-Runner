#include "FileSource.h"
#include <chrono>
#include <thread>
#include <sstream>
#include <iostream>

FileSource::FileSource(const std::string& path, double rate)
    : filePath(path), samplingRate(rate) {
    inputFile.open(filePath, std::ios::in);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    
    std::cout << "[FileSource] Opened file: " << filePath << std::endl;
}

FileSource::~FileSource() {
    if (inputFile.is_open()) {
        inputFile.close();
    }
}

double FileSource::getNextSample() {
    std::string line;

    // Wait if EOF is reached
    while (!std::getline(inputFile, line)) {
        if (inputFile.eof()) {
            inputFile.clear(); 
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue; 
        } else {
            std::cerr << "[FileSource] Failed to read from file\n";
            return 0.0;
        }
    }

    try {
        double value = std::stod(line);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000.0 / samplingRate)));
        return value;
    } catch (const std::exception& e) {
        std::cerr << "[FileSource] Failed to parse line: " << line << " (" << e.what() << ")\n";
        return 0.0;
    }
}
