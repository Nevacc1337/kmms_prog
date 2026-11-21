target_sources(${PROJECT_NAME}
	PRIVATE
		qt_game_map.cpp
		qt_game_view.cpp
		qt_sprites.cpp
		qt_ui_factory.cpp
		qt_ui_obj_rect_adapter.cpp
		"${CMAKE_CURRENT_SOURCE_DIR}/sprites.qrc"
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_subdirectory(ui_objects)
