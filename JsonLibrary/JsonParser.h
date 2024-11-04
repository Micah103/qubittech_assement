#pragma once

#include "JsonObject.h"
#include "JsonArray.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <memory>
#include <iostream> // Include iostream for debugging output
#include <algorithm> // Include algorithm for std::remove

class JsonParser {
public:
    static std::shared_ptr<JsonObject> parseObject(const std::string& jsonText) {
        std::istringstream iss(jsonText);
        return parseObject(iss);
    }

    static std::shared_ptr<JsonArray> parseArray(const std::string& jsonText) {
        std::istringstream iss(jsonText);
        return parseArray(iss);
    }

private:
    static std::shared_ptr<JsonObject> parseObject(std::istringstream& iss) {
        skipWhitespace(iss);
        if (iss.eof() || iss.get() != '{') {
            throw std::runtime_error("Expected '{' at the start of JSON object or unexpected end of input");
        }

        auto jsonObject = std::make_shared<JsonObject>();
        skipWhitespace(iss);

        while (iss.peek() != '}') {
            std::string key = parseString(iss);
            skipWhitespace(iss);
            if (iss.eof() || iss.get() != ':') {
                throw std::runtime_error("Expected ':' after key in JSON object or unexpected end of input");
            }
            JsonValue value = parseValue(iss);
            jsonObject->add(key, value);

            skipWhitespace(iss);
            if (iss.peek() == ',') {
                iss.get();
            }
            skipWhitespace(iss);
        }

        if (iss.eof() || iss.get() != '}') {
            throw std::runtime_error("Expected '}' at the end of JSON object or unexpected end of input");
        }
        return jsonObject;
    }

    static std::shared_ptr<JsonArray> parseArray(std::istringstream& iss) {
        skipWhitespace(iss);
        if (iss.eof() || iss.get() != '[') {
            throw std::runtime_error("Expected '[' at the start of JSON array or unexpected end of input");
        }

        auto jsonArray = std::make_shared<JsonArray>();
        skipWhitespace(iss);

        while (iss.peek() != ']') {
            JsonValue value = parseValue(iss);
            jsonArray->add(value);

            skipWhitespace(iss);
            if (iss.peek() == ',') {
                iss.get();
            }
            skipWhitespace(iss);
        }

        if (iss.eof() || iss.get() != ']') {
            throw std::runtime_error("Expected ']' at the end of JSON array or unexpected end of input");
        }
        return jsonArray;
    }

    static JsonValue parseValue(std::istringstream& iss) {
        skipWhitespace(iss);
        char c = iss.peek();

        if (c == '"') {
            return parseString(iss);
        }
        else if ((c >= '0' && c <= '9') || c == '-') {
            return parseNumber(iss);
        }
        else if (c == 't' || c == 'f') {
            return parseBool(iss);
        }
        else if (c == 'n') {
            iss.get(); iss.get(); iss.get(); iss.get(); // Consume "null"
            return nullptr; // Assuming JsonValue can be a nullptr
        }
        else if (c == '{') {
            return parseObject(iss);
        }
        else if (c == '[') {
            return parseArray(iss);
        }
        else {
            throw std::runtime_error("Invalid JSON value");
        }
    }

    static std::string parseString(std::istringstream& iss) {
        std::string result;
        if (iss.eof() || iss.get() != '"') {
            throw std::runtime_error("Expected '\"' at start of JSON string or unexpected end of input");
        }

        char c;
        while (iss.get(c)) {
            if (c == '"') {
                return result;
            }
            if (c == '\\') { // Handle escaped characters
                if (iss.peek() == '"') iss.get(c);
                else if (iss.peek() == '\\') iss.get(c);
                else if (iss.peek() == 'n') { iss.get(c); result += '\n'; continue; }
                else if (iss.peek() == 't') { iss.get(c); result += '\t'; continue; }
                else if (iss.peek() == 'r') { iss.get(c); result += '\r'; continue; }
                else if (iss.peek() == 'b') { iss.get(c); result += '\b'; continue; }
                else if (iss.peek() == 'f') { iss.get(c); result += '\f'; continue; }
            }
            result += c;
        }
        throw std::runtime_error("Unexpected end of input while parsing string");
    }

    // Change from double to int
    static JsonValue parseNumber(std::istringstream& iss) {
        int number;
        iss >> number;

        if (iss.fail()) {
            throw std::runtime_error("Invalid number format");
        }
        return number; // Return as int
    }

    static bool parseBool(std::istringstream& iss) {
        std::string boolStr;
        iss >> boolStr; // Read "true" or "false"

        // Debugging output
        std::cout << "Parsing boolean: '" << boolStr << "'" << std::endl;

        // Trim whitespace and potential trailing commas
        boolStr.erase(std::remove(boolStr.begin(), boolStr.end(), ','), boolStr.end());

        if (boolStr == "true") return true;
        else if (boolStr == "false") return false;
        else throw std::runtime_error("Invalid JSON boolean value");
    }

    static void skipWhitespace(std::istringstream& iss) {
        while (isspace(iss.peek())) iss.get();
    }
};
