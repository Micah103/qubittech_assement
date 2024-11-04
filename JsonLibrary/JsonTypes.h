#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <variant>
#include <memory>

// Forward declarations for JsonObject and JsonArray
class JsonObject;
class JsonArray;

// Define JsonValue as a variant to hold different JSON types
using JsonValue = std::variant<std::string, int, bool, std::nullptr_t, std::shared_ptr<JsonObject>, std::shared_ptr<JsonArray>>;
