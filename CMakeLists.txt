cmake_minimum_required(VERSION 3.12)
project(raytracer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)




