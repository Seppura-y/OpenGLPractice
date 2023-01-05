cmake_minimum_required(VERSION 3.22)
project(app_lib)

file(GLOB_RECURSE ${PROJECT_NAME}_HEADER "./*.h")
file(GLOB_RECURSE ${PROJECT_NAME}_SRC "./*.cpp")

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_SRC})

