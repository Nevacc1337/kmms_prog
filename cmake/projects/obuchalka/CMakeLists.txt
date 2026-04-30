add_executable(menu
    src/main.cpp
    src/menuFunctions.cpp
    src/menuItems.cpp
)

target_include_directories(menu PRIVATE src)