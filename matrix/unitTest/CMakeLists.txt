cmake_minimum_required(VERSION 3.23.1)

project(matrixTest VERSION 1.0.0  LANGUAGES CXX)
add_executable(${PROJECT_NAME} matrixTest.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -c -g -std=c++17 -Wall -W -Werror -pedantic)
target_include_directories(${PROJECT_NAME} PUBLIC . ../)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

enable_testing()

target_link_libraries(${PROJECT_NAME} gtest gtest_main pthread)
#target_link_libraries(${PROJECT_NAME} matrix)
#include(GoogleTest)
#add_test(NAME matrixTest COMMAND mTest)