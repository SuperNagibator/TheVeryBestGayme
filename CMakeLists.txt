cmake_minimum_required(VERSION 3.15)
project(TheVeryBestGayme VERSION 0.0.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} src/main.cpp src/Application.cpp src/Shader.cpp)

add_library(glad glad/src/gl.c)
target_include_directories(glad PUBLIC glad/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)