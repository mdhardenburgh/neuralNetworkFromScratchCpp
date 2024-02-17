# Set project name and version of CMAKE to use
cmake_minimum_required(VERSION 3.23.1)
project(matrix VERSION 1.0)

# Tell cmake to generate an interface library
# Interface libary is generally for header only libraries that aren't compiled to be linked later
add_library(${PROJECT_NAME} INTERFACE)

# Make headers available to those that include this library
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})