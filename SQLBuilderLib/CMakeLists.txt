cmake_minimum_required(VERSION 3.10)

# Project name
project(SQLBuilderORMTest)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add SQLite library for linking
find_package(SQLite3 REQUIRED)

# Add executable and link with SQLite3
add_executable(SQLBuilderORMTest main.cpp SQLBuilder.cpp)
target_link_libraries(SQLBuilderORMTest SQLite::SQLite3)
