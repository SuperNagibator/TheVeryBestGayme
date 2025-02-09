cmake_minimum_required(VERSION 3.15)
project(TheVeryBestGayme VERSION 0.0.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(glad glad/src/gl.c)
target_include_directories(glad PUBLIC glad/include)

find_package(glfw3 CONFIG REQUIRED)
find_package(SPNG CONFIG REQUIRED)

add_executable(
    ${PROJECT_NAME} 
    src/main.cpp 
    src/Application.cpp 
    src/Resource.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/Mesh.cpp
)

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE 
    glad
    glfw
    $<IF:$<TARGET_EXISTS:spng::spng>,spng::spng,spng::spng_static>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -DPROJECT_NAME="${PROJECT_NAME}")