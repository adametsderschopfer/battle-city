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

        src/Renderer/VertexBuffer.cpp
        src/Renderer/VertexBuffer.h
        src/Renderer/IndexBuffer.cpp
        src/Renderer/IndexBuffer.h
        src/Renderer/VertexArray.cpp
        src/Renderer/VertexArray.h

        src/Game/Game.cpp
        src/Game/Game.h
        src/Game/GameObjects/Tank.cpp
        src/Game/GameObjects/Tank.h
        src/Renderer/VertexBufferLayout.cpp
        src/Renderer/VertexBufferLayout.h
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer.h
        src/Core/GameObject.cpp
        src/Core/GameObject.h
        src/Game/Level.cpp
        src/Game/Level.h
        src/Game/GameObjects/BrickWall.cpp
        src/Game/GameObjects/BrickWall.h
        src/Renderer/SpriteAnimator.cpp
        src/Renderer/SpriteAnimator.h
        src/Game/GameObjects/ConcreteWall.cpp
        src/Game/GameObjects/ConcreteWall.h
        src/Game/GameObjects/Trees.cpp
        src/Game/GameObjects/Trees.h
        src/Game/GameObjects/Ice.cpp
        src/Game/GameObjects/Ice.h
        src/Game/GameObjects/Water.cpp
        src/Game/GameObjects/Water.h
        src/Game/GameObjects/Eagle.cpp
        src/Game/GameObjects/Eagle.h
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

include_directories(external/rapidjson/include)

set_target_properties(
        ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)