cmake_minimum_required(VERSION 3.16)
project(kvcc C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-Wall -Wextra)

# uthash — 헤더 하나짜리 해시테이블 라이브러리. 빌드할 게 없어서(순수 매크로),
# FetchContent로 소스만 받아 include 경로에 추가하면 끝난다. 설치 단계 없음 —
# cmake가 설정 시점에 알아서 받아온다.
include(FetchContent)
FetchContent_Declare(
  uthash
  GIT_REPOSITORY https://github.com/troydhanson/uthash.git
  GIT_TAG v2.4.0
)
FetchContent_MakeAvailable(uthash)

add_executable(kvcc
  src/main.c
  src/server.c
  src/client.c
  src/store.c
)
target_include_directories(kvcc PRIVATE include ${uthash_SOURCE_DIR}/src)
