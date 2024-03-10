cmake_minimum_required(VERSION 3.26)
project(GatorAVLTree)

set(CMAKE_CXX_STANDARD 14)

#recommended by aman to match test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

#pull in desired version of catch through cmake automatically, make it available
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)

include_directories(test-unit)
include_directories(src)

add_executable(Main
        src/main.cpp # your main
        src/Tree.cpp src/Student.cpp src/Tree.h src/Student.h)

#this one doesn't include main, instead having your test.cpp
add_executable(Tests #this will be named Project1 by default - either change it to Tests or see the comment at the bottom of the file
        test-unit/test.cpp # your test file
        src/Tree.cpp src/Student.cpp src/Tree.h src/Student.h)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain) #link catch to test.cpp file
#if your testing executable is named Project1, change Tests in the line above to Project1