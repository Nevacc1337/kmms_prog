set(SOURCES
    ln_test.cpp
)

add_executable(ln_test ${SOURCES})

target_link_libraries(ln_test
    ${LIBRARY}
    gtest_main
    gmock_main
)

add_test(ln_test ln_test)
