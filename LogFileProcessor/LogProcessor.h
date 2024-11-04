#pragma once
#include <string>
#include <vector>
#include <thread>
#include <fstream>

// LogProcessor class: Responsible for reading and processing log files,
// and saving processed results to a database.
class LogProcessor {
public:
    // Constructor: Initializes the LogProcessor with the specified log file path
    LogProcessor(const std::string& logFilePath);

    // ProcessLogs: Reads the log file, processes each line using multiple threads,
    // and saves results to the database.
    void processLogs();

private:
    // ProcessLine: Processes a single line from the log file and saves the result to the database
    void processLine(const std::string& line);

    // SaveToDatabase: Saves the processed result to the database
    void saveToDatabase(const std::string& result);

    std::string logFilePath; // Path to the log file to be processed
};
