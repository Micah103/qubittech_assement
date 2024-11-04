#include <iostream>
#include "SQLBuilder.h"
#include "ORM.h"

// User class for ORM example
class User {
public:
    User() : id(0), age(0) {}

    // Getter methods
    std::string getName() const { return name; }
    int getAge() const { return age; }
    int getId() const { return id; }

    // Setter methods
    void setName(const std::string& name) { this->name = name; }
    void setAge(int age) { this->age = age; }
    void setId(int id) { this->id = id; }

private:
    std::string name;
    int age;
    int id;
};

void createUserTable(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "age INTEGER NOT NULL);";

    char* errMsg;
    int exit = sqlite3_exec(db, sql, nullptr, 0, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

int main() {
    // Initialize database and create users table
    ORM<User> orm;  // This will open the database
    createUserTable(orm.getDb()); // Assume getDb() gives access to the database

    // Test SQLBuilder
    SQLBuilder builder;
    std::string query = builder.SELECT("*").FROM("users").WHERE("age > 18").build();
    std::cout << "Generated Query: " << query << std::endl;

    // Test ORM functionality
    User user;
    user.setName("Rahim");
    user.setAge(21);
    user.setId(1);

    orm.save(user);  // Save user
    user.setAge(22); // Update age
    orm.update(user);  // Update user
    auto foundUser = orm.findById(1);  // Find user by ID

    if (foundUser) {
        std::cout << "Found User: " << foundUser->getName() << ", Age: " << foundUser->getAge() << std::endl;
    }
    else {
        std::cout << "User not found." << std::endl;
    }

    return 0;
}
