cmake_minimum_required(VERSION 3.15)
project(pa2-task2)
set(CMAKE_CXX_STANDARD 14)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-long-long")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -c")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

add_executable(pa2-task2 main.cpp)