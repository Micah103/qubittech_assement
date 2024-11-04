#include "LogProcessor.h"

int main() {
    // Define the path to the log file to be processed
    std::string logFilePath = "../logfile.txt";

    // Create a LogProcessor instance with the specified log file path
    LogProcessor logProcessor(logFilePath);

    // Start processing the logs, reading the file and saving results to the database
    logProcessor.processLogs();

    return 0; // Return success status
}
