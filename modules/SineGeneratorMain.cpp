#include "SineGenerator.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: SineGeneratorMain <frequency> <amplitude> <sampling_rate>\n";
        return 1;
    }

    double freq = std::stod(argv[1]);
    double amp = std::stod(argv[2]);
    double rate = std::stod(argv[3]);

    SineGenerator generator(freq, amp, rate);

    while (true) {
        double sample = generator.getNextSample();
        std::cout.write(reinterpret_cast<char*>(&sample), sizeof(sample));
        std::cout.flush();
    }

    return 0;
}
