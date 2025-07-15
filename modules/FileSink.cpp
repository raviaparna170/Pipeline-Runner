#include "FileSink.h"
#include <iostream>
#include<thread>

FileSink::FileSink(const std::string& filePath) {
    outputFile.open(filePath);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    } else {
        std::cout << "[FileSink] Opened file: " << filePath << std::endl;
    }
}


FileSink::~FileSink() {
    if (outputFile.is_open()) {
        outputFile.close();
        std::cout << "[FileSink] File closed.\n";
    }
}

void FileSink::send(double sample) {
    if (outputFile.is_open()) {
        outputFile << sample << "\n";
        outputFile.flush();
        std::cout << "[FileSink] Wrote sample: " << sample << std::endl;
    } else {
        std::cerr << "[FileSink] Output file is not open!" << std::endl;
    }
    //std::cout << "[FileSink] Thread: " << std::this_thread::get_id() 
    //      << " - Wrote sample: " << sample << std::endl;

}

