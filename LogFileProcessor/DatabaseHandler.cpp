#include "DatabaseHandler.h"
#include <iostream>

// Constructor: Opens the database and creates the table if it doesn't exist
DatabaseHandler::DatabaseHandler() {
    int exit = sqlite3_open("logdata.db", &db);
    if (exit != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
    createTableIfNotExists(); // Ensure the Logs table exists
}

// Destructor: Closes the database connection
DatabaseHandler::~DatabaseHandler() {
    sqlite3_close(db);
}

// CreateTableIfNotExists: Creates the Logs table if it does not already exist
void DatabaseHandler::createTableIfNotExists() {
    const char* sql = "CREATE TABLE IF NOT EXISTS Logs ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "data TEXT NOT NULL);";

    char* errMsg;
    int exit = sqlite3_exec(db, sql, nullptr, 0, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg); // Free the error message memory
    }
}

// Save: Inserts the provided log data into the Logs table
void DatabaseHandler::save(const std::string& data) {
    const char* sql = "INSERT INTO Logs (data) VALUES (?);";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement for execution
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, data.c_str(), -1, SQLITE_STATIC); // Bind the data to the statement
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error inserting data: " << sqlite3_errmsg(db) << std::endl; // Handle insertion error
        }
    }
    else {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl; // Handle preparation error
    }

    sqlite3_finalize(stmt); // Clean up the prepared statement
}
