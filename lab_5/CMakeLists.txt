cmake_minimum_required(VERSION 3.10)

project(Manager VERSION 1.0 LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/main_window.cpp
	src/main_window.h)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)