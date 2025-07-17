#include "FileSource.h"
#include <unistd.h> // write
#include <iostream>
#include <cstdlib>  // for std::stod

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: FileSourceMain <file_path> <sampling_rate>\n";
        return 1;
    }

    std::string filePath = argv[1];
    double samplingRate = std::stod(argv[2]);

    FileSource source(filePath, samplingRate);

    while (true) {
        double sample = source.getNextSample();
        ssize_t written = write(STDOUT_FILENO, &sample, sizeof(sample));
        if (written != sizeof(sample)) {
            std::cerr << "[FileSourceMain] Failed to write sample\n";
            break;
        }
    }

    return 0;
}
