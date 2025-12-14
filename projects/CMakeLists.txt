cmake_minimum_required(VERSION 3.10)
project(projects)

enable_testing()   # ← ВАЖНО

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(obuchaika)
add_subdirectory(sort)
