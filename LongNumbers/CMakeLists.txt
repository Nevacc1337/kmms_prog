cmake_minimum_required(VERSION 3.14)
project(long_numbers VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- GoogleTest (downloaded automatically) ---
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Library ---
add_library(long_number
    src/long_number.cpp
)
target_include_directories(long_number PUBLIC src)

# --- Tests ---
enable_testing()
add_subdirectory(test)
