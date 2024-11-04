
# Interview C++ Coding Solutions

This project includes solutions to five coding questions implemented in C++. The solutions are optimized for clarity, efficiency, and portability. Detailed setup and run instructions are provided for each question, using **CMake** in a **Kali Linux environment** with **Visual Studio Code**.

## Table of Contents

- [Project Overview](#project-overview)
- [Environment Setup](#environment-setup)
  - [Requirements](#requirements)
  - [Build Instructions](#build-instructions)
- [Individual Question Descriptions](#individual-question-descriptions)
  - [Question 1: Message Fragmentation Library](#question-4-message-fragmentation-library)
  - [Question 2: SQL Builder Library](#question-2-sql-builder-library)
  - [Question 3: TCP Proxy Server](#question-3-tcp-proxy-server)
  - [Question 4: JSON Parser](#question-5-json-parser)
  - [Question 5: Log File Processor](#question-1-log-file-processor)
- [Running Each Question](#running-each-question)
- [Additional Notes](#additional-notes)

---

## Project Overview

This project serves as an advanced, multi-faceted preparation for technical interviews, focusing on backend and systems programming. Each coding question is organized into standalone sections, allowing you to compile and run each question independently.

## Environment Setup

This project requires a **Linux environment** (Kali Linux is recommended) and has been developed in **Visual Studio Code**. **CMake** is used as the build system for cross-platform compatibility.

### Requirements

- **Linux Distribution**: Kali Linux is used for development.
- **CMake**: Required for building the project. Install CMake if not already available on your system:
  ```bash
  sudo apt-get update
  sudo apt-get install cmake
  ```
- **SQLite**: Required for questions involving database operations (e.g., SQL Builder Library).
- **Visual Studio Code**: Used as the IDE.

### Build Instructions

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```

2. **Run CMake to configure and build the project**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Set Up Database (if applicable)**:
   - Ensure the database files are located correctly if required by specific questions (e.g., `logdata.db` for the Log File Processor).

---

## Individual Question Descriptions

### Question 1: Log File Processor

- **Description**: Reads large log files, processes each line using multithreading, and stores results in a database.
- **Technologies**: C++, SQLite, CMake
- **Key Components**:
  - `LogProcessor` class: Handles file reading and processing.
  - `DatabaseHandler` class: Manages database connections and writes processed log entries.

### Question 2: SQL Builder Library

- **Description**: Implements an SQL Builder library using chain-style methods for constructing SQL queries.
- **Technologies**: C++, CMake
- **Key Components**:
  - `SQLBuilder` class: Supports query building.
  - ORM (Object-Relational Mapping) integration for simple mapping between objects and database tables.

### Question 3: TCP Proxy Server

- **Description**: A multithreaded TCP Proxy Server capable of handling high volumes of connections (up to 1000 simultaneous).
- **Technologies**: C++, Sockets, CMake
- **Key Components**:
  - `TCPServer` and `ThreadPool` classes: Manage incoming connections, distribute load over a 5-thread pool, and handle logging.

### Question 4: Message Fragmentation Library

- **Description**: Splits long messages into smaller chunks, reassembles fragments, and manages missing or corrupted data.
- **Technologies**: C++, CMake
- **Key Components**:
  - `Fragmenter` and `MessageAssembler` classes: Implement message fragmentation, reassembly, and error handling.

### Question 5: JSON Parser

- **Description**: A lightweight JSON parser that reads JSON strings and outputs structured data.
- **Technologies**: C++, CMake
- **Key Components**:
  - `JsonParser` class: Parses JSON strings into structured objects.
  - `JsonTypes` for handling specific JSON data types (e.g., arrays, objects, booleans).

---

## Running Each Question

This section provides command-line instructions for running each solution individually. Ensure you've built the project as described in the [Build Instructions](#build-instructions).

### Running Question 1: Log File Processor

1. **Navigate to the build folder**:
   ```bash
   cd ~/Desktop/LogFileProcessor/build
   ```

2. **Run the LogProcessor**:
   ```bash
   ./LogProcessor
   ```

   - **Note**: Place `logfile.txt` in the same directory or specify the path within the code.

### Running Question 2: SQL Builder Library

1. **Navigate to the SQL Builder Library build folder**:
   ```bash
   cd ~/Desktop/SQLBuilderLib/build
   ```

2. **Run the SQL Builder example**:
   ```bash
   ./SQLBuilderExample
   ```

   - **Note**: Database operations will output queries generated using the chain-style methods.

### Running Question 3: TCP Proxy Server

1. **Navigate to the TCP Proxy Server build folder**:
   ```bash
   cd ~/Desktop/TCPProxyServer/build
   ```

2. **Run the Proxy Server**:
   ```bash
   ./TCPProxyServer
   ```

   - **Testing**: Use **Postman** or **Perf** for load testing, or any compatible client to test server responses.

### Running Question 4: Message Fragmentation Library

1. **Navigate to the Message Fragmentation Library build folder**:
   ```bash
   cd ~/Desktop/MessageFragmentationLibrary/build
   ```

2. **Run the Message Fragmentation example**:
   ```bash
   ./MessageFragmentationExample
   ```

   - **Functionality**: Processes and reassembles fragmented messages, with error handling output to the console.

### Running Question 5: JSON Parser

1. **Navigate to the JSON Parser build folder**:
   ```bash
   cd ~/Desktop/JsonLibrary/build
   ```

2. **Run the JSON Parser example**:
   ```bash
   ./JsonParser
   ```

   - **Functionality**: Parses JSON input, outputs structured data to the console.

---

## Additional Notes

- **Database Files**: Ensure any database files (e.g., `logdata.db`) are in the correct directory to avoid file access issues.
- **Error Handling**: Each program includes logging for error handling to aid debugging.
- **Threading and Performance**: Optimizations, such as threading for concurrent processing, are implemented in solutions where high performance is needed (e.g., Log Processor and TCP Proxy Server).

---

This README should provide all necessary setup, run, and usage information to make the most of this project as a complete interview preparation tool! Let me know if you’d like further customization.
