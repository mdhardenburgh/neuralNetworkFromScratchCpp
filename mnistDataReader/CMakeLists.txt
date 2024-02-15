cmake_minimum_required(VERSION 3.23.1)
project(mnistDataReader VERSION 1.0)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})