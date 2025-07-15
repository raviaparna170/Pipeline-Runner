# Build Instructions for Real-Time Streaming Data Pipeline

This document provides step-by-step instructions to build and run the project on a system using **CMake** and **Ninja** build system with **MSYS2 (UCRT64)** on Windows.

---

## Prerequisites

1. **C++ Compiler** with C++17 support (e.g., GCC via MSYS2)
2. **CMake** (version 3.16 or higher)
3. **Ninja** build system
4. **MSYS2 with UCRT64 environment**
5. **Internet access** (for fetching GoogleTest via CMake)

---

## Build Steps

1. Clone the Repository
- git clone https://github.com/raviaparna170/Pipeline-Runner.git
- cd Pipeline-Runner
2. Create a Build Directory
- mkdir build
- cd build

3. Run CMake Configuration
- cmake ..
- ninja
If successful, you'll get two executables:
PipelineApp.exe → Main application
runTests.exe → GoogleTest unit test suite

4. Run the Application
- ./PipelineApp.exe --config=../config/config.json
- ./runTests.exe

Ensure the input/output paths in the config JSON file exist and are accessible.
Make sure test input files (like test_input.txt) are placed correctly (usually in ../tests/ relative to the build directory).

5. Output Files
Logs and output samples are written to the path specified in config.json under the output section.
Example output file: ../output/results.txt

