cmake_minimum_required(VERSION 3.15)
project(vernead2)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-long-long")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")

include_directories(src_old/include)

file(GLOB_RECURSE sources "src_old/*.cpp")
list(REMOVE_ITEM sources "${CMAKE_SOURCE_DIR}/src/cmd.cpp")

add_executable(main src/Interface/cmd.cpp ${sources})
target_link_libraries(main jpeg png)

add_executable(test2 tests/testUtils.cpp ${sources})
target_link_libraries(test2 jpeg png)

add_executable(test3 tests/testImageGetter.cpp ${sources})
target_link_libraries(test3 jpeg png)

add_executable(test4 tests/testJPEGConverter.cpp ${sources})
target_link_libraries(test4 jpeg png)

add_executable(test5 tests/testPNGConverter.cpp ${sources})
target_link_libraries(test5 jpeg png )

add_executable(test6 tests/megaTest.cpp ${sources})
target_link_libraries(test6 jpeg png)

add_executable(test7 tests/testFilters.cpp ${sources})
target_link_libraries(test7 jpeg png)

add_executable(test8 tests/testAll.cpp ${sources})
target_link_libraries(test8 jpeg png)

add_executable(test9 tests/testPixels.cpp ${sources})
target_link_libraries(test9 jpeg png)