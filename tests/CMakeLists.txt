cmake_minimum_required(VERSION 3.5)
project(tests)

set(CMAKE_CXX_STANDARD 11)

# Locate the necessary libraries
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# Include the source directory
include_directories(${PROJECT_SOURCE_DIR}/../main/src)

# Add the test executable
add_executable(test_module test_module.cpp)

# Link the necessary libraries
target_link_libraries(test_module PRIVATE GTest::GTest GTest::Main Threads::Threads)
