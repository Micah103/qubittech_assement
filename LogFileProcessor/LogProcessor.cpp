#include "LogProcessor.h"
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <fstream>
#include "DatabaseHandler.h"

std::mutex dbMutex;     // Mutex for database access to prevent concurrent write issues
std::mutex consoleMutex; // Mutex for synchronizing console output to avoid garbled text

// Constructor: Initializes the LogProcessor with the specified log file path
LogProcessor::LogProcessor(const std::string& logFilePath) : logFilePath(logFilePath) {}

// ProcessLogs: Reads the log file line by line and spawns threads to process each line
void LogProcessor::processLogs() {
    std::ifstream logFile(logFilePath);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file.\n";
        return;
    }

    std::cerr << "Log file opened successfully.\n"; // Debug message

    std::vector<std::thread> threads; // Vector to hold threads for processing
    std::string line;

    // Read each line from the log file
    while (std::getline(logFile, line)) {
        if (!line.empty()) { // Ensure the line is not empty before processing
            threads.emplace_back(&LogProcessor::processLine, this, line); // Create a thread for processing the line
        }
    }

    // Join all threads to ensure completion before exiting
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join(); // Wait for each thread to finish
        }
    }
}

// ProcessLine: Processes a single line from the log file
void LogProcessor::processLine(const std::string& line) {
    // Process the line (placeholder logic)
    std::string processedData = "Processed: " + line;

    // Lock console output to prevent interleaving
    {
        std::lock_guard<std::mutex> lock(consoleMutex);
        std::cout << "Processing line: " << line << std::endl; // Log each line processed
    }

    // Lock and save to the database to prevent race conditions
    {
        std::lock_guard<std::mutex> lock(dbMutex);
        saveToDatabase(processedData); // Save processed data to the database
    }

    // Log the data saved to the console
    {
        std::lock_guard<std::mutex> lock(consoleMutex);
        std::cout << "Data saved: " << processedData << std::endl; // Log confirmation of data saved
    }
}

// SaveToDatabase: Saves the processed result to the database
void LogProcessor::saveToDatabase(const std::string& result) {
    DatabaseHandler dbHandler; // Create a DatabaseHandler instance
    dbHandler.save(result); // Save the result to the database
}
