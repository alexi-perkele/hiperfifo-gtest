cmake_minimum_required(VERSION 3.3)
project(HiperFifo-Gtest C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_iostreams")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(hiperfifo)

set(SOURCE_FILES main.cpp hfifo.cpp)


add_executable(runtest ${SOURCE_FILES})


target_link_libraries(runtest ${GTEST_LIBRARIES} pthread)


