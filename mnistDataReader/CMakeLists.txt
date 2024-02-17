# Set project name, CMAKE version and languages
cmake_minimum_required(VERSION 3.23.1)
project(mnistDataReader VERSION 1.0 LANGUAGES CXX)

# Tell cmake to generate a library object file to be linked later
add_library(${PROJECT_NAME} OBJECT)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources for the library object file
target_sources(${PROJECT_NAME} PRIVATE mnistDataReader.cpp )

# Dependencies on other libraries
target_link_libraries(${PROJECT_NAME} matrix)
# Compile options, ie: strict C++, all warnings as errors, C++ version, etc...
target_compile_options(${PROJECT_NAME} PRIVATE -c -g -std=c++17 -Wall -W -Werror -pedantic)

# Make headers available to those that include this library
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})