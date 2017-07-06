cmake_minimum_required(VERSION 2.8)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/config.h.in
    ${PROJECT_SOURCE_DIR}/src/config.h
)

include(CheckSymbolExists)
CHECK_SYMBOL_EXISTS(pow math.h HAVE_POW)

if (HAVE_POW)
    option (USE_POW ON)
endif()

add_executable(main src/main.cpp src/config.h)
