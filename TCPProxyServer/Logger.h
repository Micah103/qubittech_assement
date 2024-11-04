
#ifndef LOGGER_H // Include guard to prevent multiple inclusions of this header file
#define LOGGER_H

#include <fstream> // Include for file stream operations
#include <mutex>   // Include for mutex to ensure thread safety
#include <string>  // Include for using the std::string type

// Logger class declaration
class Logger {
public:
    // Constructor: Initializes the logger with a filename to write logs to
    Logger(const std::string& filename);

    // Destructor: Cleans up resources used by the logger
    ~Logger();

    // Method to log a message to the log file
    void log(const std::string& message);

private:
    std::ofstream logFile; // Output file stream for logging to a file
    std::mutex mtx;        // Mutex for thread-safe logging to prevent data races
};

#endif // LOGGER_H // End of include guard
