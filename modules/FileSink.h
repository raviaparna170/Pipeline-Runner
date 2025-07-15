#ifndef FILESINK_H
#define FILESINK_H

#include "../core/IOutputSink.h"
#include <fstream>
#include <string>

class FileSink : public IOutputSink {
public:
    FileSink(const std::string& filename);
    ~FileSink();

    void send(double sample) override;

private:
    std::ofstream outputFile;
};

#endif 
