if(GAME_TYPE STREQUAL "WindowsConsole")
	target_sources(${PROJECT_NAME} PRIVATE windows_app_factory.cpp)
elseif(GAME_TYPE STREQUAL "LinuxConsole")
	target_sources(${PROJECT_NAME} PRIVATE linux_app_factory.cpp)
elseif(GAME_TYPE STREQUAL "Qt")
	target_sources(${PROJECT_NAME} PRIVATE qt_app_factory.cpp)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
