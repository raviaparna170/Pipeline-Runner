#pragma once

#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include "../core/IDataSource.h"
#include "../core/ITransformation.h"
#include "../core/IOutputSink.h"
#include "../core/ThreadSafeQueue.h"

class PipelineRunner {
public:
    PipelineRunner(const std::string& configPath);
    void run();

private:
    void loadConfig(const std::string& path);

    std::unique_ptr<IDataSource> source;
    std::vector<std::unique_ptr<ITransformation>> transformations;
    std::vector<std::unique_ptr<IOutputSink>> sinks;

    ThreadSafeQueue<double> sourceQueue;
    ThreadSafeQueue<double> transformQueue;

    std::thread sourceThread;
    std::thread transformThread;
    std::thread sinkThread;

    std::atomic<bool> running = true;
};
