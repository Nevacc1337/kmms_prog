project(tests)

set(LIBRARY
	shell_sort_lib555
)

add_library(${LIBRARY} "")

add_subdirectory(src)
add_subdirectory(test)