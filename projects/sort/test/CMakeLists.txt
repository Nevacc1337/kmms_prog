# Отключаем GoogleMock (он ломается на GCC 15)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/googletest googletest)

enable_testing()

add_executable(test_bubble
    test_bubble.cpp
)

target_link_libraries(test_bubble
    sort_lib
    gtest
    gtest_main
)

add_test(NAME bubble_test COMMAND test_bubble)
