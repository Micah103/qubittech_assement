#include "Json.h"
#include <iostream>

int main() {
    // Sample JSON input
    std::string jsonText = R"({"name": "Rahim", "age": 21, "isStudent": false, "scores": [88, 92, 79]})";
    std::cout << "Input JSON: " << jsonText << std::endl; // Print the input JSON

    try {
        // Task 1: Parse the JSON string into a JsonObject
        auto obj = JsonParser::parseObject(jsonText);

        // Task 2: Display original values
        std::string name = std::get<std::string>(obj->get("name"));
        int age = std::get<int>(obj->get("age")); // Use int for age
        bool isStudent = std::get<bool>(obj->get("isStudent"));

        std::cout << "\n--- Original Values ---" << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl; // Output as integer
        std::cout << "Is Student: " << (isStudent ? "true" : "false") << std::endl;

        // Task 3: Display scores
        auto scores = std::get<std::shared_ptr<JsonArray>>(obj->get("scores"));
        std::cout << "Scores: ";
        for (size_t i = 0; i < scores->values.size(); ++i) {
            std::cout << std::get<int>(scores->get(i)) << (i < scores->values.size() - 1 ? ", " : "");
        }
        std::cout << std::endl;
        std::cout << "\n--- Modify Values ---" << std::endl;

        // Task 4: Modify the JsonObject
        obj->add("grade", std::string("A")); // Adding a new key-value pair
        std::cout << "Added grade: " << std::get<std::string>(obj->get("grade")) << std::endl;

        // Update existing value
        obj->remove("age"); // Remove the old age
        age++; // Increment age
        obj->add("age", age); // Add the new age as integer
        std::cout << "Updated age to: " << std::get<int>(obj->get("age")) << std::endl; // Output the updated age

        // Remove a key-value pair
        obj->remove("isStudent");
        std::cout << "Removed key 'isStudent'" << std::endl;

        // Task 5: Serialize the updated JsonObject back to a JSON string
        std::string updatedJson = obj->toString();
        std::cout << "\n--- Updated JSON ---" << std::endl;
        std::cout << updatedJson << std::endl; // Print the updated JSON

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; // Handle parsing or runtime errors
    }

    return 0;
}
