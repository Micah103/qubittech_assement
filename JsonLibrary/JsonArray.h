#pragma once

#include "JsonTypes.h"
#include <sstream>
#include <stdexcept>
#include <vector>

// Forward declaration to avoid circular dependency issues
std::string jsonValueToString(const JsonValue& value);

/**
 * @class JsonArray
 * @brief Represents a JSON array.
 *
 * A JsonArray stores a list of values, which can be any valid JSON type.
 */
class JsonArray {
public:
    std::vector<JsonValue> values;

    // Add a value to the JsonArray
    void add(const JsonValue& value) {
        values.push_back(value);
    }

    // Remove a value by index from the JsonArray
    void remove(size_t index) {
        if (index >= values.size()) {
            throw std::runtime_error("Index out of range in JsonArray");
        }
        values.erase(values.begin() + index);
    }

    // Retrieve a value by index
    JsonValue get(size_t index) const {
        if (index < values.size()) {
            return values[index];
        }
        else {
            throw std::runtime_error("Index out of range in JsonArray");
        }
    }

    // Convert JsonArray to JSON string
    std::string toString() const {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < values.size(); ++i) {
            if (i > 0) oss << ",";
            oss << jsonValueToString(values[i]);
        }
        oss << "]";
        return oss.str();
    }
};
