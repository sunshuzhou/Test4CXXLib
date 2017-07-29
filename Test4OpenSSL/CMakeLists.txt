cmake_minimum_required(VERSION 2.8)

project(Test4OpenSSL)

set(LIBRARIES "")

# Boost
find_package(Boost REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})
set(LIBRARIES ${LIBRARIES} ${Boost_LIBRARIES})

# OpenSSL
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
#set(LIBRARIES "${LIBRARIES} ${OPENSSL_SSL_LIBRARY}")
set(LIBRARIES ${LIBRARIES} ${OPENSSL_CRYPTO_LIBRARY})

# C++11
set(CMAKE_CXX_STANDARD 11)

aux_source_directory(. MAIN_SRC)
aux_source_directory(rfc RFC_SRC)
add_executable(${PROJECT_NAME} ${MAIN_SRC} ${RFC_SRC})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
