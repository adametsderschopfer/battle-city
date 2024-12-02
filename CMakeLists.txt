cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(PROJECT_NAME battle_city)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
        src/main.cpp

        src/Resources/ResourceManager.cpp
        src/Resources/ResourceManager.h
        src/Resources/stb_image.h

        src/Renderer/ShaderProgram.cpp
        src/Renderer/ShaderProgram.h
        src/Renderer/Texture2D.cpp
        src/Renderer/Texture2D.h
        src/Renderer/Sprite.cpp
        src/Renderer/Sprite.h
        src/Renderer/AnimatedSprite.cpp
        src/Renderer/AnimatedSprite.h

        src/Renderer/VertexBuffer.cpp
        src/Renderer/VertexBuffer.h
        src/Renderer/IndexBuffer.cpp
        src/Renderer/IndexBuffer.h

        src/Game/Game.cpp
        src/Game/Game.h
        src/Game/Tank.cpp
        src/Game/Tank.h
)

set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

include_directories(external/glm)

set_target_properties(
        ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)