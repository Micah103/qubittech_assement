
#include "Logger.h" // Include the header file for the Logger class

// Constructor: Initializes the logger by opening the specified log file
Logger::Logger(const std::string& filename) {
    // Open the log file in append mode; create it if it doesn't exist
    logFile.open(filename, std::ios::out | std::ios::app);
}

// Destructor: Closes the log file if it is open
Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close(); // Close the log file to free resources
    }
}

// Method to log a message to the log file
void Logger::log(const std::string& message) {
    // Lock the mutex to prevent concurrent access to the log file
    std::lock_guard<std::mutex> lock(mtx);
    logFile << message << std::endl; // Write the message followed by a newline
}
