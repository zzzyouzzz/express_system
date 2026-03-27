cmake_minimum_required(VERSION 3.10)
project(express_system)

file(GLOB SOURCES src/main/*.cpp)

set(INCLUDE_DIRS src/include)
include_directories(${INCLUDE_DIRS})

add_executable(express_system ${SOURCES})
