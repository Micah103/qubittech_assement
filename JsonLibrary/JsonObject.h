#pragma once

#include "JsonTypes.h"
#include "JsonArray.h"
#include <unordered_map>
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>

// Forward declaration to avoid circular dependency issues
std::string jsonValueToString(const JsonValue& value);

/**
 * @class JsonObject
 * @brief Represents a JSON object.
 *
 * A JsonObject stores key-value pairs where keys are strings and values can be
 * various JSON types including other objects or arrays.
 */
class JsonObject {
public:
    std::unordered_map<std::string, JsonValue> values;

    // Add a key-value pair to the JsonObject
    void add(const std::string& key, const JsonValue& value) {
        // Check for existing key
        if (values.find(key) != values.end()) {
            throw std::runtime_error("Key already exists in JsonObject");
        }
        values[key] = value;
    }

    // Remove a key-value pair from the JsonObject
    void remove(const std::string& key) {
        if (values.erase(key) == 0) {
            throw std::runtime_error("Key not found in JsonObject");
        }
    }

    // Retrieve a value by key
    JsonValue get(const std::string& key) const {
        auto it = values.find(key);
        if (it != values.end()) {
            return it->second;
        }
        else {
            throw std::runtime_error("Key not found in JsonObject");
        }
    }

    // Check if a key exists in the JsonObject
    bool contains(const std::string& key) const {
        return values.find(key) != values.end();
    }

    // Convert JsonObject to JSON string
    std::string toString() const {
        std::ostringstream oss;
        oss << "{";
        for (auto it = values.begin(); it != values.end(); ++it) {
            if (it != values.begin()) oss << ",";
            oss << "\"" << it->first << "\":" << jsonValueToString(it->second);
        }
        oss << "}";
        return oss.str();
    }
};

// Helper function to convert JsonValue to string for serialization
inline std::string jsonValueToString(const JsonValue& value) {
    if (std::holds_alternative<std::string>(value)) {
        return "\"" + std::get<std::string>(value) + "\"";
    }
    else if (std::holds_alternative<int>(value)) { // Change from double to int
        return std::to_string(std::get<int>(value));
    }
    else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? "true" : "false";
    }
    else if (std::holds_alternative<std::nullptr_t>(value)) {
        return "null";
    }
    else if (std::holds_alternative<std::shared_ptr<JsonObject>>(value)) {
        return std::get<std::shared_ptr<JsonObject>>(value)->toString();
    }
    else if (std::holds_alternative<std::shared_ptr<JsonArray>>(value)) {
        return std::get<std::shared_ptr<JsonArray>>(value)->toString();
    }
    return "";
}

