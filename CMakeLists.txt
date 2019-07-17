cmake_minimum_required(VERSION 2.6)

project(fastops)

include_directories("${PROJECT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

add_subdirectory(fastops)
add_subdirectory(tools)
