cmake_minimum_required(VERSION 3.26)
project(GatorAVLTree)

set(CMAKE_CXX_STANDARD 14)

#recommended by aman to match test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

include_directories(test-unit)
include_directories(src)

add_executable(Main
        src/main.cpp # your main
        src/Tree.cpp src/Student.cpp src/Tree.h src/Student.h)