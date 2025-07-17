cmake_minimum_required(VERSION 3.16)
project(PipelineApp)

set(CMAKE_CXX_STANDARD 17)

# ========= Boost Manual Install Path =========
set(BOOST_ROOT "C:/Users/aruna/Downloads/boost_1_88_0/boost_1_88_0")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")

# ========= Find Boost Components =========
#find_package(Boost REQUIRED COMPONENTS process system thread filesystem program_options date_time)
find_package(Boost REQUIRED COMPONENTS system thread filesystem program_options date_time)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# ========= Project Include Paths =========
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

# ========= Main Pipeline Library =========
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

# ========= Main Executable =========
add_executable(PipelineApp main.cpp)
target_link_libraries(PipelineApp PRIVATE pipeline_lib ${Boost_LIBRARIES})

# ========= POSIX Threading Support =========
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

# ========= Stage Binaries (for individual stages) =========
add_executable(SineGeneratorMain modules/SineGeneratorMain.cpp modules/SineGenerator.cpp)
target_link_libraries(SineGeneratorMain PRIVATE pipeline_lib ${Boost_LIBRARIES})

add_executable(FileSourceMain modules/FileSourceMain.cpp modules/FileSource.cpp)
target_link_libraries(FileSourceMain PRIVATE ${Boost_LIBRARIES})

add_executable(FFTMain modules/FFTMain.cpp modules/FFT.cpp external/kissfft/kiss_fft.c)
target_link_libraries(FFTMain PRIVATE ${Boost_LIBRARIES})

add_executable(FileSinkMain modules/FileSinkMain.cpp modules/FileSink.cpp)
target_link_libraries(FileSinkMain PRIVATE ${Boost_LIBRARIES})

# ========= Pipeline Runner as Process =========
#add_executable(PipelineRunnerProcess pipeline/PipelineRunnerProcess.cpp external/kissfft/kiss_fft.c)
#target_include_directories(PipelineRunnerProcess PRIVATE ${CMAKE_SOURCE_DIR}/external/kissfft)
#target_link_libraries(PipelineRunnerProcess PRIVATE ${Boost_LIBRARIES})

add_executable(PipelineRunnerProcess pipeline/PipelineRunnerProcess.cpp external/kissfft/kiss_fft.c)

target_include_directories(PipelineRunnerProcess PRIVATE
    ${CMAKE_SOURCE_DIR}/external/kissfft
    ${BOOST_INCLUDEDIR}   
)

target_link_libraries(PipelineRunnerProcess PRIVATE ${Boost_LIBRARIES})

