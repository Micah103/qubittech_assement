cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(JsonParser VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable target
add_executable(JsonParser main.cpp)

# Include directories (if you have a specific include directory structure)
target_include_directories(JsonParser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# If you have additional libraries to link, you can do it here
# target_link_libraries(JsonParser PRIVATE <library_name>)

# If you want to add tests, you can include them here or in a separate folder
# enable_testing()
# add_subdirectory(tests)

# Optional: Set up installation rules
install(TARGETS JsonParser DESTINATION bin)
