set(SOURCES
	testSorts.cpp
)

add_executable(testSorts ${SOURCES})
target_link_libraries(testSorts
	gtest_main
	gmock_main
	sorts_lib
)

add_test(testSorts testSorts)