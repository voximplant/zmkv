cmake_minimum_required(VERSION 2.8)
project(zmkv_example)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../zmkv/cmake/")
find_package(ebml REQUIRED)
find_package(matroska REQUIRED)

include_directories(../zmkv/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



set(SOURCE_FILES main.cpp)
add_executable(zmkv_example ${SOURCE_FILES})
target_link_libraries(zmkv_example zmkv ${MATROSKA_LIBRARIES} ${EBML_LIBRARIES})