cmake_minimum_required(VERSION 3.14)
project(YourProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматически скачиваем свежий GoogleTest (совместим с GCC 15)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# Для MinGW иногда нужно это
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Подключаем подпроекты
add_subdirectory(menu)
add_subdirectory(sorts)   # или sort, если папка называется sort