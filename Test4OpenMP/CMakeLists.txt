cmake_minimum_required(VERSION 3.7)
project(Test4OpenMP)

find_package(OpenMP)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_CXX_STANDARD 11)

    set(SOURCE_FILES main.cpp)
add_executable(Test4OpenMP ${SOURCE_FILES})
