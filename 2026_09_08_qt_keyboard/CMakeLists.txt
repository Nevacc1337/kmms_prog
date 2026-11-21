cmake_minimum_required(VERSION 3.16)
project(keyboard LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
# Нужен для классов с Q_OBJECT (сигналы и слоты)
set(CMAKE_AUTOMOC ON)
 
find_package(Qt6 REQUIRED COMPONENTS Widgets)
 
add_executable(keyboard
    src/main.cpp
    src/keyboard.cpp
    src/keyboard_button.cpp
    src/keyboard_data.cpp
    src/keyboard_window.cpp
    src/mood_face.cpp
    src/welcome_window.cpp
)
 
target_link_libraries(keyboard PRIVATE Qt6::Widgets)
 