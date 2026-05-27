target_sources(sorts_lib
	PRIVATE
		sorts.cpp
	PUBLIC
		sorts.hpp
)

target_include_directories(sorts_lib PUBLIC
	"${PROJECT_SOURCE_DIR}/src"
)