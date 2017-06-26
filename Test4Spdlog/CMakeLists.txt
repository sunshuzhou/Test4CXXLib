cmake_minimum_required(VERSION 2.8)
project(Test4Spdlog)
include_directories(.)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-std=c++0x)
endif()

find_package (Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp )

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

