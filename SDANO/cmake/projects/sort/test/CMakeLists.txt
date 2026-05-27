# Подключаем GoogleTest из подмодуля
add_subdirectory(../lib/googletest googletest_build)

enable_testing()

add_executable(test_bubble
    test_bubble.cpp
)

target_link_libraries(test_bubble
    bubble_sort
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_bubble)