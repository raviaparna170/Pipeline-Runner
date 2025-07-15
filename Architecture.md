# Architecture: Pipeline Runner

## Overview

This system is designed to ingest, process, and output streaming data in real-time. It uses a modular and multithreaded architecture to ensure low latency and efficient processing.

---

## 1. Process Model

- **Single-process, Multithreaded Architecture**
  - The entire pipeline runs within a single process.
  - It spawns **three main threads**:
    - **Source Thread** – reads data from an input source (file or sine generator).
    - **Transform Thread** – applies transformation(s) (e.g., FFT) on the data.
    - **Sink Thread** – writes the processed data to an output (e.g., file).

---

## 2. Communication Model

- **In-memory thread-safe queues** are used to pass data between stages.
- Each stage operates independently and pushes/pulls data to/from its respective queue.
- This decouples components and enables parallel processing.

```plaintext
        +---------+     +---------------+     +----------+
        | Source  | --> | Transformation | --> | Sink     |
        +---------+     +---------------+     +----------+
            |                  |                   |
      [sourceQueue]     [transformQueue]      [output]
```
---

## 3. Configuration and Orchestration Strategy

The pipeline is fully configurable via a JSON file
ConfigParser parses this file and sets up
- Input source (e.g., file or sine generator).
- List of transformations (FFT, filters).
- Output sink (e.g., file writer).

## 4. Modularity

Each stage implements interfaces defined in core/:
- IDataSource → implemented by FileSource, SineGenerator
- ITransformation → implemented by FFT
- IOutputSink → implemented by FileSink
This design makes it easy to plug in new modules (e.g., network sink, new filter) with minimal changes.

## 5.  Fault Tolerance and Extensibility

Each thread is isolated; a failure in one does not crash others. Queues can be monitored for overflow or blocking.

Easy to extend:
- Add new transformations (e.g., IIR, FIR).
- Add new sinks (e.g., WebSocketSink, DatabaseSink).
- Add real-time plotting or analytics.

## Dependencies

- C++17
- KissFFT – lightweight FFT library
- GoogleTest – for unit testing
- nlohmann/json – for JSON parsing