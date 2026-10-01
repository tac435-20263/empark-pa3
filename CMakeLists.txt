# Require CMAKE 3.20 or higher
cmake_minimum_required(VERSION 3.20)

# Project name
project(pa3)

# Build for C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Any source files in this directory
set(SOURCE_FILES Main.cpp)

# Where any include files are
include_directories(src)

# Subdirectories to build
add_subdirectory(src)
add_subdirectory(tests)

# Name of executable
add_executable(main ${SOURCE_FILES})

# Link main vs the source library
target_link_libraries(main src)
