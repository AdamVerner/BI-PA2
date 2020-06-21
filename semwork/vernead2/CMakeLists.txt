cmake_minimum_required(VERSION 3.15)
project(vernead2)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-long-long")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-delete-non-virtual-dtor")


include_directories(src/)

file(GLOB_RECURSE sources "src/*.cpp")
list(REMOVE_ITEM sources "${CMAKE_SOURCE_DIR}/src/Interface/cmd.cpp")

add_executable(main src/Interface/main.cpp ${sources})
target_link_libraries(main jpeg png)

add_executable(testScaler tests/testScaler.cpp ${sources})
target_link_libraries(testScaler jpeg png)

add_executable(testImageGetter tests/testImageGetter.cpp ${sources})
target_link_libraries(testImageGetter jpeg png)

add_executable(testPixels tests/testPixels.cpp ${sources})
target_link_libraries(testScaler jpeg png)

add_executable(testFilters tests/testFilters.cpp ${sources})
target_link_libraries(testFilters jpeg png)
