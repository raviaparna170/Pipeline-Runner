#include "FFT.h"
#include <unistd.h>
#include <cstring>
#include <iostream>

int main() {
    FFT fft;
    double inputSample;

    while (read(STDIN_FILENO, &inputSample, sizeof(inputSample)) == sizeof(inputSample)) {
        auto result = fft.process(inputSample);
        if (result.has_value()) {
            double outSample = result.value();
            ssize_t written = write(STDOUT_FILENO, &outSample, sizeof(outSample));
            if (written != sizeof(outSample)) {
                std::cerr << "[FFTMain] Failed to write FFT result\n";
                break;
            }
        }
    }

    return 0;
}
