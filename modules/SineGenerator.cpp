#include "SineGenerator.h"
#include<thread>
#include <chrono>
#include<iostream>


SineGenerator::SineGenerator(double frequency, double amplitude, double samplingRate): frequency(frequency), amplitude(amplitude), samplingRate(samplingRate), time(0.0) 
{
    startTime = std::chrono::steady_clock::now();
}

double SineGenerator::getNextSample() {
    using namespace std::chrono;

    // Time elapsed since start
    auto now = steady_clock::now();
    duration<double> elapsed = now - startTime;

    // Calculate sine wave sample at current time
    double sample = amplitude * std::sin(2 * M_PI * frequency * elapsed.count());
    //std::cout << "[SineGenerator] Thread: " << std::this_thread::get_id() 
          //<< " - Generated sample: " << sample << std::endl;

    // Wait until next sample should be generated (simulate real-time)
    std::this_thread::sleep_for(std::chrono::duration<double>(1.0 / samplingRate));

    return sample;
}