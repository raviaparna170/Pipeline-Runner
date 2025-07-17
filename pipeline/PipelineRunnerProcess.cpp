#include <boost/process.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <vector>

using json = nlohmann::json;
namespace bp = boost::process;

int main(int argc, char* argv[]) {
    std::ifstream configFile("../config/config.json");
    if (!configFile.is_open()) {
        std::cerr << "Failed to open config file.\n";
        return 1;
    }

    json config;
    configFile >> config;

    bp::child sourceProc, transformProc, sinkProc;
    bp::ipstream fromSource;
    bp::ipstream fromTransform;

    // source
    std::string sourceType = config["source"]["type"];
    std::vector<std::string> sourceArgs;

    if (sourceType == "sine") {
        const auto& sine = config["source"]["sine"];
        sourceArgs = {
            "--freq", std::to_string(sine["frequency"]),
            "--amplitude", std::to_string(sine["amplitude"]),
            "--rate", std::to_string(sine["sampling_rate"])
        };
        sourceProc = bp::child("./SineGeneratorMain", bp::args(sourceArgs), bp::std_out > fromSource);

    } else if (sourceType == "file") {
        const auto& file = config["source"]["file"];
        sourceArgs = {
            "--path", file["path"],
            "--rate", std::to_string(file["sampling_rate"])
        };
        sourceProc = bp::child("./FileSourceMain", bp::args(sourceArgs), bp::std_out > fromSource);

    } else {
        std::cerr << "Unsupported source type: " << sourceType << std::endl;
        return 1;
    }

    // ytransform
    if (!config["pipeline"].empty()) {
        std::string transformType = config["pipeline"][0]["type"];

        if (transformType == "fft") {
            transformProc = bp::child("./FFTMain", bp::std_in < fromSource, bp::std_out > fromTransform);
        } else {
            std::cerr << "Unsupported transform type: " << transformType << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Pipeline is empty.\n";
        return 1;
    }

    // sink
    const auto& output = config["output"][0];
    std::string sinkType = output["type"];
    std::vector<std::string> sinkArgs;

    if (sinkType == "file") {
        sinkArgs = { "--path", output["path"] };
        sinkProc = bp::child("./FileSinkMain", bp::args(sinkArgs), bp::std_in < fromTransform);
    } else {
        std::cerr << "Unsupported sink type: " << sinkType << std::endl;
        return 1;
    }

    
    sourceProc.wait();
    transformProc.wait();
    sinkProc.wait();

    std::cout << "Pipeline execution complete.\n";
    return 0;
}
