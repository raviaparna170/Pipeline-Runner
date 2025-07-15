#include <iostream>
#include "pipeline/PipelineRunner.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./pipeline_runner --config config/config.json\n";
        return 1;
    }

	std::string configPath;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.find("--config=") == 0) {
            configPath = arg.substr(9);
        }
    }

	if (configPath.empty()) {
        std::cerr << "Missing --config=<file> argument.\n";
        return 1;
    }

	try {
        PipelineRunner runner(configPath);
        runner.run();
		} catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}