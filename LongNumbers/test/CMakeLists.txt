add_executable(test_long_number
    test_long_number.cpp
)

target_link_libraries(test_long_number
    PRIVATE
        long_number
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_long_number)
