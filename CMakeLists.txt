cmake_minimum_required(VERSION 3.30)
project(avx LANGUAGES CXX)

include(CheckCXXCompilerFlag)

set(CMAK_CXX_STANDARD 17)
set(CMAK_CXX_STANDARD_REQUIRED ON)

# avx512
CHECK_CXX_COMPILER_FLAG("-mavx512f" AVX512_BUILD)
if(NOT AVX512_BUILD)
    message(FATAL_ERROR "avx512 support not found!")
endif()

set(CMAKE_CXX_FLAGS "-mavx512f -O0")
include_directories(include)
add_library(dotop src/dot.cpp)

target_include_directories(dotop PUBLIC $(PROJECT_SOURCE_DIR)/include)

add_executable(runner runner.cpp)
target_link_libraries(runner PRIVATE dotop)
