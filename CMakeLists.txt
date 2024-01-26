cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 REQUIRED COMPONENTS SDL3)
add_executable(untitled src/main.cpp
        src/Game/Game.h
        src/Game/Game.cpp)
target_link_libraries(untitled PRIVATE SDL3::SDL3)