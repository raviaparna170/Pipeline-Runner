cmake_minimum_required(VERSION 3.16)
project(PipelineApp)

set(CMAKE_CXX_STANDARD 17)

# Add include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/modules
    ${CMAKE_SOURCE_DIR}/pipeline
    ${CMAKE_SOURCE_DIR}/config
    ${CMAKE_SOURCE_DIR}/external/json
    ${CMAKE_SOURCE_DIR}/external/kissfft
)

# ========= External: KissFFT =========
add_library(kissfft STATIC external/kissfft/kiss_fft.c)
target_include_directories(kissfft PUBLIC external/kissfft)

# ========= Main Library: pipeline_lib =========
add_library(pipeline_lib
    core/IDataSource.h
    core/ITransformation.h
    core/IOutputSink.h

    modules/SineGenerator.cpp
    modules/FileSource.cpp
    modules/FileSink.cpp
    modules/FFT.cpp

    pipeline/PipelineRunner.cpp
    config/ConfigParser.cpp
)

target_link_libraries(pipeline_lib PUBLIC kissfft)

# ========= Executable: PipelineApp =========
add_executable(PipelineApp main.cpp)
target_link_libraries(PipelineApp PRIVATE pipeline_lib)

# Link pthreads if on Unix
if(UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(PipelineApp PRIVATE Threads::Threads)
endif()

# ========= GoogleTest Setup =========
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ========= Test Executable =========
add_executable(runTests
    tests/test_main.cpp
    tests/test_fft.cpp
    tests/test_filesource.cpp
)

target_link_libraries(runTests
    pipeline_lib
    gtest_main
    gtest
)

include(GoogleTest)
gtest_discover_tests(runTests)
