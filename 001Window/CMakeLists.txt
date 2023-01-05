cmake_minimum_required(VERSION 3.22)
project(Window)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(application)

add_executable(Window "main.cpp")

target_link_libraries(Window app_lib)

target_link_options(${PROJECT_NAME} PRIVATE 
	"/subsystem:console"
	"/entry:WinMainCRTStartup"
)