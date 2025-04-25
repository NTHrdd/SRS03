cmake_minimum_required(VERSION 3.10)

project(SRS03)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
        Task1.cpp
        morse_translator.h
        morse_translator.cpp)

