cmake_minimum_required(VERSION 3.3)
project(runtest C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_iostreams -pthread")

#find_package(Boost REQUIRED)
find_package(Boost COMPONENTS iostreams REQUIRED)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

#include_directories(${GTEST_INCLUDE_DIRS})
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)


add_subdirectory(hiperfifo)

set(SOURCE_FILES main.cpp hfifo.cpp hfifo_test.cpp)

add_executable(runtest ${SOURCE_FILES})

target_link_libraries(runtest gtest_main pthread ${Boost_LIBRARIES})







