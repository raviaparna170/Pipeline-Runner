#pragma once

#include "../core/IDataSource.h"
#include <fstream>
#include <string>

class FileSource : public IDataSource {
public:
    FileSource(const std::string& path, double rate);
    ~FileSource();

    double getNextSample() override;

private:
    std::string filePath;
    std::ifstream inputFile;
    double samplingRate;
	std::ifstream fileStream;
};
