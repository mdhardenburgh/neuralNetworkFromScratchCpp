# CMakeLists files in this project can
# refer to the root source directory of the project as ${JetsonNanoRegisterAccess_SOURCE_DIR} and
# to the root binary directory of the project as ${JetsonNanoRegisterAccess_BINARY_DIR}.

# Set CMAKE version project name and languages
cmake_minimum_required(VERSION 3.23.1)
project(neuralNetFromScratch VERSION 1.0.0 LANGUAGES CXX)

# Tell cmake to generate an executable
add_executable(${PROJECT_NAME} ${SOURCES})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell cmake to recurse into the follow directories and run the cmake scrite in there
add_subdirectory(matrix)
add_subdirectory(mnistDataReader)

# Specifiy target sources
target_sources(${PROJECT_NAME} PUBLIC main.cpp)
# Specifiy dependencies on other libraries
target_link_libraries(${PROJECT_NAME} matrix mnistDataReader)
# Compile options, ie: strict C++, all warnings as errors, C++ version, etc...
target_compile_options(${PROJECT_NAME} PRIVATE -c -g -std=c++17 -Wall -W -Werror -pedantic)

#find_package(Qt6 REQUIRED COMPONENTS Core)
#qt_standard_project_setup()

#qt_add_executable(helloworld
#    main.cpp
#)
#
#target_link_libraries(helloworld PRIVATE Qt6::Core)