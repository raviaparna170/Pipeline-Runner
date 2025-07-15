#include "PipelineRunner.h"
#include "../modules/SineGenerator.h"
#include "../modules/FFT.h"
#include "../modules/FileSource.h"
#include "../modules/FileSink.h"
#include "../config/ConfigParser.h"
#include <iostream>
#include <thread>

#include "../core/IDataSource.h"
#include "../core/ITransformation.h"
#include "../core/IOutputSink.h"

PipelineRunner::PipelineRunner(const std::string& configPath) {
    loadConfig(configPath);
}

void PipelineRunner::loadConfig(const std::string& path) {
    auto config = ConfigParser::parse(path);

    const std::string sourceType = config["source"]["type"];
    if (sourceType == "sine") {
        double freq = config["source"]["sine"]["frequency"];
        double amp = config["source"]["sine"]["amplitude"];
        double rate = config["source"]["sine"]["sampling_rate"];
        source = std::make_unique<SineGenerator>(freq, amp, rate);
    } else if (sourceType == "file") {
        std::string path = config["source"]["file"]["path"];
        int rate = config["source"]["file"]["sampling_rate"];
        source = std::make_unique<FileSource>(path, rate);
    } else {
        throw std::runtime_error("Unknown source type: " + sourceType);
    }

    for (const auto& t : config["pipeline"]) {
        if (t["type"] == "fft") {
            transformations.push_back(std::make_unique<FFT>());
        }
    }

    for (const auto& o : config["output"]) {
        if (o["type"] == "file") {
            sinks.push_back(std::make_unique<FileSink>(o["path"]));
        }
    }
}

void PipelineRunner::run() {
    std::cout << "[PipelineRunner] Starting multithreaded pipeline...\n";

    // Thread 1: Source
    sourceThread = std::thread([&]() {
        while (running) {
            double sample = source->getNextSample();
            sourceQueue.push(sample);
        }
    });

    // Thread 2: Transform
    transformThread = std::thread([&]() {
        while (running) {
            double sample;
            sourceQueue.pop(sample);

            for (auto& transform : transformations) {
                auto result = transform->process(sample);
                if (!result.has_value()) {
                    
                    goto skip_push;
                }
                sample = result.value();
            }

            transformQueue.push(sample);
        skip_push:
            continue;
        }
    });

    // Thread 3: Sink
    sinkThread = std::thread([&]() {
        while (running) {
            double sample;
            transformQueue.pop(sample);

            for (auto& sink : sinks) {
                sink->send(sample);
            }
        }
    });

    sourceThread.join();
    transformThread.join();
    sinkThread.join();
}
