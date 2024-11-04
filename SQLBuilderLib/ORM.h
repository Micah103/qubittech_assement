#pragma once
#include <sqlite3.h>     // SQLite library for database operations
#include <string>        // Standard string library
#include <memory>        // Memory library for smart pointers
#include <map>           // Map library for key-value data storage
#include <iostream>      // For output to console
#include "SQLBuilder.h"  // Custom SQLBuilder for building SQL queries

// ORM template class for handling database interactions for objects of type T
template <typename T>
class ORM {
public:
    ORM() {
        // Open the SQLite database connection
        int exit = sqlite3_open("logdata.db", &db);
        if (exit != SQLITE_OK) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        }
    }

    ~ORM() {
        // Close the SQLite database connection
        sqlite3_close(db);
    }

    bool save(const T& obj) {
        SQLBuilder builder;  // Instance of SQLBuilder to construct SQL statements
        std::map<std::string, std::string> values = {
            {"name", obj.getName()},       // obj has `getName()` method
            {"age", std::to_string(obj.getAge())}  // obj has `getAge()` method
        };

        std::string query = builder.INSERT("users", values).build();  // Build SQL INSERT query
        std::cout << "Executing query: " << query << std::endl;

        sqlite3_stmt* stmt;  // SQLite statement to execute
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            if (sqlite3_step(stmt) != SQLITE_DONE) {  // Execute the INSERT statement
                std::cerr << "Error inserting data: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_finalize(stmt);  // Release resources for the statement
                return false;
            }
        }
        else {
            std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);  // Finalize statement after execution
        return true;  // Return success
    }

    bool update(const T& obj) {
        SQLBuilder builder;  // SQLBuilder instance for constructing SQL queries
        std::map<std::string, std::string> values = {
            {"name", obj.getName()},            // Map field name to object name value
            {"age", std::to_string(obj.getAge())}  // Map field age to object age value
        };

        // Build SQL UPDATE query to update specific record by ID
        std::string query = builder.UPDATE("users").SET(values).WHERE("id = " + std::to_string(obj.getId())).build();
        std::cout << "Executing query: " << query << std::endl;

        sqlite3_stmt* stmt;  // SQLite statement to prepare and execute
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            if (sqlite3_step(stmt) != SQLITE_DONE) {  // Execute the UPDATE statement
                std::cerr << "Error updating data: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_finalize(stmt);  // Release resources for the statement
                return false;
            }
        }
        else {
            std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);  // Finalize statement after execution
        return true;  // Return success
    }

    std::shared_ptr<T> findById(int id) {
        SQLBuilder builder;  // SQLBuilder instance for constructing SELECT query
        std::string query = builder.SELECT("*").FROM("users").WHERE("id = " + std::to_string(id)).build();
        std::cout << "Executing query: " << query << std::endl;

        sqlite3_stmt* stmt;  // SQLite statement to prepare and execute
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            if (sqlite3_step(stmt) == SQLITE_ROW) {  // Execute the SELECT statement and fetch results
                std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));  // Get name from result
                int age = sqlite3_column_int(stmt, 2);  // Get age from result
                auto obj = std::make_shared<T>();  // Create shared pointer for object of type T
                obj->setName(name);  // Set name for object
                obj->setAge(age);    // Set age for object
                sqlite3_finalize(stmt);  // Release statement resources
                return obj;  // Return object with populated data
            }
        }
        else {
            std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);  // Release statement resources
        return nullptr;  // Return nullptr if not found
    }

    sqlite3* getDb() const { return db; }  // Getter for the database connection

private:
    sqlite3* db;  // Database connection handle
};
