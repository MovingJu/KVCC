cmake_minimum_required(VERSION 3.16)
project(kvcc C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-Wall -Wextra)

add_executable(kvcc
  src/main.c
  src/server.c
  src/client.c
)
target_include_directories(kvcc PRIVATE include)
