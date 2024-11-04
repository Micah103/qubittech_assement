#include "SQLBuilder.h"

SQLBuilder& SQLBuilder::SELECT(const std::string& fields) {
    query += "SELECT " + fields + " ";
    return *this;
}

SQLBuilder& SQLBuilder::FROM(const std::string& table) {
    query += "FROM " + table + " ";
    return *this;
}

SQLBuilder& SQLBuilder::WHERE(const std::string& condition) {
    query += "WHERE " + condition + " ";
    return *this;
}

SQLBuilder& SQLBuilder::JOIN(const std::string& table, const std::string& condition) {
    query += "JOIN " + table + " ON " + condition + " ";
    return *this;
}

SQLBuilder& SQLBuilder::INSERT(const std::string& table, const std::map<std::string, std::string>& values) {
    query += "INSERT INTO " + table + " (";
    for (auto it = values.begin(); it != values.end(); ++it) {
        query += it->first + (std::next(it) != values.end() ? ", " : "");
    }
    query += ") VALUES (";
    for (auto it = values.begin(); it != values.end(); ++it) {
        query += "'" + it->second + "'" + (std::next(it) != values.end() ? ", " : "");
    }
    query += ") ";
    return *this;
}

SQLBuilder& SQLBuilder::UPDATE(const std::string& table) {
    query += "UPDATE " + table + " ";
    return *this;
}

SQLBuilder& SQLBuilder::SET(const std::map<std::string, std::string>& values) {
    query += "SET ";
    for (auto it = values.begin(); it != values.end(); ++it) {
        query += it->first + " = '" + it->second + "'" + (std::next(it) != values.end() ? ", " : "");
    }
    query += " ";
    return *this;
}

std::string SQLBuilder::build() {
    return query + ";";
}
