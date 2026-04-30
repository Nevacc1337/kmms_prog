project(long_numbers)

set(LIBRARY "ln_lib")

add_library(${LIBRARY} "")

add_subdirectory(src)
add_subdirectory(test)
