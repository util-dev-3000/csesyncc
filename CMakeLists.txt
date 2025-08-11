cmake_minimum_required(VERSION 3.15)
project(csesyncc VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.c")

add_executable(csesyncc ${SOURCES})

target_include_directories(csesyncc PRIVATE include)