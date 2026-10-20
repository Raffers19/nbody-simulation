
cmake_minimum_required(VERSION 3.20)

project(NBodySimulation LANGUAGES CXX)

# Require standard C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable CTest
enable_testing()

# Process the source directory
add_subdirectory(src)

# Process the test directory
add_subdirectory(tests)
