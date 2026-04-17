cmake_minimum_required(VERSION 3.30)
project(avx LANGUAGES CXX)

find_package(GTest REQUIRED)

include(CheckCXXSourceCompiles)

set(CMAK_CXX_STANDARD 17)
set(CMAK_CXX_STANDARD_REQUIRED ON)

# avx512
set(AVX512CODE "
#include <immintrin.h>
int main() {
    __m512 a = _mm512_set1_ps(1.0f);
    return 0;
}
")
CHECK_CXX_SOURCE_COMPILES("${AVX512CODE}" AVX512BUILD)

if(NOT AVX512_BUILD)
    message(FATAL_ERROR "avx512 support not found!")
else()
    message(STATUS "avx512 detected...")
endif()

set(CMAKE_CXX_FLAGS "-mavx512f -O0")
include_directories(include)
add_library(dotop src/dot.cpp)

target_include_directories(dotop PUBLIC $(PROJECT_SOURCE_DIR)/include)

add_executable(runner runner.cpp)
target_link_libraries(runner PRIVATE dotop)

# Tests
add_executable(utests 
    tests/test_main.cpp
    tests/test_dotop.cpp
    )
target_link_libraries(utests 
GTest::gtest
GTest::gtest_main
dotop
)

include(GoogleTest)
gtest_discover_tests(utests)