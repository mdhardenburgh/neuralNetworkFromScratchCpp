cmake_minimum_required(VERSION 3.23.1)

project(neuralNetFromScratch VERSION 1.0.0 LANGUAGES CXX)
#target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")
#target_compile_options(${PROJECT_NAME} PRIVATE -c -g -std=c++17 -Wall -W -pedantic)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES main.cpp)
add_executable(neuralNetFromScratch ${SOURCES})

#find_package(Qt6 REQUIRED COMPONENTS Core)
#qt_standard_project_setup()

#qt_add_executable(helloworld
#    main.cpp
#)
#
#target_link_libraries(helloworld PRIVATE Qt6::Core)