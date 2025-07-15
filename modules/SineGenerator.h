#ifndef SINEGENERATOR_H
#define SINEGENERATOR_H

#include <cmath>
#include <chrono>
#include <thread>
#include "IDataSource.h"


class SineGenerator : public IDataSource {
public:
    SineGenerator(double freq, double amp, double rate);

    double getNextSample() override;

private:
    double frequency;
    double amplitude;
    double samplingRate;
    double currentTime = 0.0;
    double time;
    std::chrono::steady_clock::time_point startTime;

};

#endif 
