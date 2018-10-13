cmake_minimum_required(VERSION 3.12)
project(raytracer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracer src/main.cpp)

target_include_directories(raytracer PUBLIC
        include
        PRIVATE src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

add_executable(test
        ${TEST_SOURCE})

target_include_directories(test PUBLIC
        include
        PRIVATE src test)


