cmake_minimum_required(VERSION 3.15)
project(pa2-task3)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-long-long")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")

include_directories(src/include)

file(GLOB sources "src/*.cpp")
list(REMOVE_ITEM sources "${CMAKE_SOURCE_DIR}/src/cmd.cpp")

add_executable(main src/cmd.cpp ${sources})

add_executable(test test.cpp ${sources})
add_executable(test2 tests/testUtils.cpp ${sources})
add_executable(test3 tests/testImageGetter.cpp ${sources})