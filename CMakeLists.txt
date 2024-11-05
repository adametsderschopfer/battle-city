cmake_minimum_required(VERSION 3.26)

set(PROJECT_NAME 2d_game_engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)
add_executable(${PROJECT_NAME} src/main.cpp)

set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)
