cmake_minimum_required(VERSION 3.20)
project(fechas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(fecha fecha.cpp)

add_executable(programa main.cpp)
target_link_libraries(programa PRIVATE fecha)

add_executable(pruebas pruebas.cpp)
target_link_libraries(pruebas PRIVATE fecha)

enable_testing()
add_test(NAME pruebas COMMAND pruebas)
