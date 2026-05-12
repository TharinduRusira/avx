cmake_minimum_required(VERSION 3.30)
project(avx LANGUAGES CXX)

# verify Linux
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Linux detected...")
else()
    message(FATAL_ERROR "This tool requires Linux environment. Exiting...")
endif()

find_package(GTest REQUIRED)

include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)

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
    set(CMAKE_CXX_FLAGS "-mavx512f -O0")
endif()

# check f16c compiler support
CHECK_CXX_COMPILER_FLAG("-mf16c" COMPILER_SUPPORTS_F16C)
# check f16c cpu support
execute_process(
    COMMAND cat /proc/cpuinfo
    COMMAND grep -o "f16c"
    OUTPUT_VARIABLE CPU_SUPPORTS_F16C
    )
string(FIND "${CPU_SUPPORTS_F16C}" "f16c" CPU_HAS_F16C)

if (COMPILER_SUPPORTS_F16C AND CPU_HAS_F16C GREATER -1)
    message(STATUS "f16c support detected...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mf16c")
else()
    message(STATUS "Building without f16c...")
endif()


include_directories(include)
add_library(dotop src/dot.cpp)

target_include_directories(dotop PUBLIC $(PROJECT_SOURCE_DIR)/include)

add_executable(runner runner.cpp)
target_link_libraries(runner PRIVATE dotop)

# Tests
add_executable(utests 
    tests/test_main.cpp
    tests/test_dotop.cpp
    tests/test_clock.cpp
    )

target_link_libraries(utests 
GTest::gtest
GTest::gtest_main
dotop
)

include(GoogleTest)
gtest_discover_tests(utests)