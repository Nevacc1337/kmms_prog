add_library(sort_lib
    bubble_sort.cpp
)

target_include_directories(sort_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
