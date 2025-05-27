cmake_minimum_required(VERSION 3.10)

project(LearnOpenGL)

configure_file(
	${CMAKE_SOURCE_DIR}/configure/root_directory.h.in
	${CMAKE_SOURCE_DIR}/root_directory.h
)

add_executable(
	LearnOpenGL
	main.cpp
)

target_link_libraries(LearnOpenGL glfw glad assimp stb_image)