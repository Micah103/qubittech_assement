#pragma once
#include <string>
#include <sqlite3.h>

// DatabaseHandler: Class to manage SQLite database operations for log data
class DatabaseHandler {
public:
    DatabaseHandler(); // Constructor: Opens the database connection and initializes the table
    ~DatabaseHandler(); // Destructor: Closes the database connection
    void save(const std::string& data); // Save: Inserts log data into the database

private:
    sqlite3* db; // Pointer to the SQLite database
    void createTableIfNotExists(); // CreateTableIfNotExists: Ensures the Logs table exists in the database
};
