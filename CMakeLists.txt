cmake_minimum_required(VERSION 3.10)
project(express_system)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${ROOT_DIR}/src)
set(INCLUDE_DIR ${SRC_DIR})
set(MAIN_DIR ${SRC_DIR})

include_directories(${INCLUDE_DIR})
file(GLOB_RECURSE SOURCES ${MAIN_DIR}/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release)

add_executable(express_system ${SOURCES})
