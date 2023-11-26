cmake_minimum_required(VERSION 3.10.0)

#project name
project (EasIno_test)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE sources main.cpp src/*.cpp src/*.h)
file(GLOB_RECURSE sources_test test/*.cpp)

add_compile_definitions(TESTING)
add_compile_definitions(CPP_STD)
add_executable(main ${sources} ${sources_test})
target_link_libraries(main ${GTEST_LIBRARIES} pthread)
