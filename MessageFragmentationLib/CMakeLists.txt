cmake_minimum_required(VERSION 3.10)

# Set the project name
project(FragmentationTest)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(FragmentationTest main.cpp Fragmenter.cpp MessageAssembler.cpp)
