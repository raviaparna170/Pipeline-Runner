#include "FileSink.h"
#include <unistd.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: SinkMain <output_file_path>\n";
        return 1;
    }

    std::string outputPath = argv[1];
    FileSink sink(outputPath);

    double sample;
    while (read(STDIN_FILENO, &sample, sizeof(sample)) == sizeof(sample)) {
        sink.send(sample);
    }

    return 0;
}
