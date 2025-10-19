cmake_minimum_required(VERSION 3.16)
project(c99c CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Find Google Test
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    # If system GTest is not found, try to download and build it
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Google Test for lexer
add_executable(lexer_unittest tests/lexer_unittest.cpp src/lexer/lexer.cpp)
target_link_libraries(lexer_unittest GTest::gtest GTest::gtest_main)
target_include_directories(lexer_unittest PRIVATE src)

# Enable testing
enable_testing()

# Add Google Test
add_test(NAME lexer_unittest COMMAND lexer_unittest)