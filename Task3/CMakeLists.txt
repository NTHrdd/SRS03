cmake_minimum_required(VERSION 3.10)

# Название проекта
project(SRS03)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME}
        Task3.cpp)

