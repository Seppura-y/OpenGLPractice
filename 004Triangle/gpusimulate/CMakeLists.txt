cmake_minimum_required(VERSION 3.22)
project(gpu_sim_lib)

file(GLOB_RECURSE ${PROJECT_NAME}_HEADER "./*.h")
file(GLOB_RECURSE ${PROJECT_NAME}_SRC "./*.cpp")

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_HEADER} ${${PROJECT_NAME}_SRC})