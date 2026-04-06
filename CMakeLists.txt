cmake_minimum_required(VERSION 4.2)
project(avx LANGUAGES CXX)

set(CMAK_CXX_STANDARD 17)
set(CMAK_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-mavx512f -O0")
include_directories(include)
add_library(dotop src/dot.cpp)

target_include_directories(dotop PUBLIC $(PROJECT_SOURCE_DIR)/include)

add_executable(runner runner.cpp)
target_link_libraries(runner PRIVATE dotop)