cmake_minimum_required(VERSION 3.20)
project(tp4_carnet_notes CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tp4
    src/main.cpp
    src/carnet.cpp
)
target_include_directories(tp4 PRIVATE include)

if(MSVC)
    target_compile_options(tp4 PRIVATE /W4)
else()
    target_compile_options(tp4 PRIVATE -Wall -Wextra -Wpedantic)
endif()