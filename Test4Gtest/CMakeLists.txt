cmake_minimum_required(VERSION 2.8)

project(Test4Gtest)

include_directories(.)
find_package(Threads)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-std=c++0x)
endif (CMAKE_COMPILER_IS_GNUCXX)

# google test
set(BUILD_GMOCK off)
set(BUILD_GTEST on)
add_subdirectory(googletest)

add_library(pow src/pow.cpp)
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} gtest pow)

enable_testing()

# tests
#add_test(check_1 ${PROJECT_NAME} 2 5)
#set_tests_properties(check_1 PROPERTIES PASS_REGULAR_EXPRESSION 32)
#add_test(check_2 ${PROJECT_NAME} 8 8)
#set_tests_properties(check_2 PROPERTIES PASS_REGULAR_EXPRESSION 16777216)

# add google tests

add_executable(pow_unittest test/pow_test.cpp)
target_link_libraries(pow_unittest gtest pow)
