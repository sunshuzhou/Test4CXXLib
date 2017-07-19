cmake_minimum_required(VERSION 2.8)

add_library(tweetnacl src/tweetnacl.c src/devurandom.c)

add_executable(main src/main.cpp)

target_link_libraries(main tweetnacl)

target_compile_options(main
    PRIVATE -std=c++11)
