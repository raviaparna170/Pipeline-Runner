
#include "FFT.h"
#include <cmath>
#include <iostream>
#include "../external/kissfft/kiss_fft.h"
#include <optional>


FFT::FFT() {}

FFT::~FFT() = default;

std::optional<double> FFT::process(double sample) {
    buffer.push_back(sample);

    if (buffer.size() == 16) {
    std::cout << "[FFT] Processing block of 16 samples..." << std::endl;

    kiss_fft_cfg cfg = kiss_fft_alloc(16, 0, nullptr, nullptr);
    std::vector<kiss_fft_cpx> in(16), out(16);

    for (int i = 0; i < 16; ++i) {
        in[i].r = buffer[i];
        in[i].i = 0.0;
    }

    kiss_fft(cfg, in.data(), out.data());

    //Return magnitude of bin 0 (DC component)
    double magnitude = std::sqrt(out[0].r * out[0].r + out[0].i * out[0].i);

    free(cfg);
    buffer.clear();  // Reset buffer
    return magnitude;
}

    return std::nullopt;  // Wait until 16 samples are available
}

