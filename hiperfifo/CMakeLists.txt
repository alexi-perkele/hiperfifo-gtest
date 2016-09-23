cmake_minimum_required(VERSION 3.3)

project(hiperfifo C CXX)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcurlpp -lcurl")

set(HIPERFIFO hiperfifo.c)

add_executable(hiperfifo ${HIPERFIFO})

target_link_libraries(hiperfifo ${CURL_LIBRARY} event)