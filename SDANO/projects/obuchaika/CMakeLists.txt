project(obuchaika)

add_executable(obuchaika
    main.cpp
    menu_functions.cpp
    menu_items.cpp
)

target_include_directories(obuchaika PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
