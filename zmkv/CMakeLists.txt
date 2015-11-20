cmake_minimum_required(VERSION 2.8)
project(zmkv)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")
message("CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
find_package(ebml REQUIRED)
find_package(matroska REQUIRED)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include ${EBML_INCLUDE_DIRS})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE ssrc ${CMAKE_CURRENT_LIST_DIR}/src/*.*)
add_library(zmkv STATIC ${ssrc})
