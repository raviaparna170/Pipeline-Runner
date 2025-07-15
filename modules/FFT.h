#pragma once
#include "../core/ITransformation.h"
#include <vector>
#include <optional>


class FFT : public ITransformation {
public:
    FFT();
   
   std::optional<double> process(double sample) override;
    ~FFT();

private:
    std::vector<double> buffer;
    size_t bufferSize;
};
