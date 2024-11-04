#pragma once
#include <string>
#include <map>

class SQLBuilder {
public:
    SQLBuilder& SELECT(const std::string& fields);
    SQLBuilder& FROM(const std::string& table);
    SQLBuilder& WHERE(const std::string& condition);
    SQLBuilder& JOIN(const std::string& table, const std::string& condition);
    SQLBuilder& INSERT(const std::string& table, const std::map<std::string, std::string>& values);
    SQLBuilder& UPDATE(const std::string& table);
    SQLBuilder& SET(const std::map<std::string, std::string>& values);

    std::string build();

private:
    std::string query;
};
