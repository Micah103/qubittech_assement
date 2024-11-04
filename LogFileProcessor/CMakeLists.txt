# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(LogProcessorProject)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Locate SQLite3 library
find_package(SQLite3 REQUIRED)

# Add the include directories for SQLite3 (if needed)
include_directories(${SQLite3_INCLUDE_DIRS})

# Add the source files for the DatabaseHandler and LogProcessor classes
set(SOURCE_FILES
    DatabaseHandler.cpp
    LogProcessor.cpp
    main.cpp
)

# Create the executable
add_executable(LogProcessor ${SOURCE_FILES})

# Link SQLite3 library to the executable
target_link_libraries(LogProcessor ${SQLite3_LIBRARIES})
