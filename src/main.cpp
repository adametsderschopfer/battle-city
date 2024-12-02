#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "iostream"
#include "chrono"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"

#include "Game/Game.h"
#include "Resources/ResourceManager.h"

glm::ivec2 g_windowSize(1024, 720);
Game g_game(g_windowSize);

void glfwWindowSizeCallback(GLFWwindow *pWindow, int width, int height) {
    g_windowSize.x = width;
    g_windowSize.y = height;

    glViewport(0, 0, g_windowSize.x, g_windowSize.y);
};

void glfwKeyCallback(GLFWwindow *pWindow, int key, int scancode, int action, int mode) {
    bool isPressed = action == GLFW_PRESS;

    switch (key) {
        case GLFW_KEY_ESCAPE: {
            if (isPressed) {
                glfwSetWindowShouldClose(pWindow, GL_TRUE);
            }
        }
    }

    g_game.setKey(key, action);
}

int main(int argc, char **argv) {
    if (!glfwInit()) {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }
    // use GLFW_OPENGL_CORE_PROFILE
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *pWindow = glfwCreateWindow(
            g_windowSize.x,
            g_windowSize.y,
            "Example window",
            nullptr,
            nullptr
    );
    if (!pWindow) {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(pWindow);
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    if (!gladLoadGL()) {
        std::cout << "gladLoadGL failed!" << std::endl;
        return -1;
    }

    glClearColor(0, 0, 0, 1);

    {
        ResourceManager::setExecutablePath(argv[0]);
        if (!g_game.init()) {
            return -1;
        }

        auto lastTime = std::chrono::high_resolution_clock::now();

        while (!glfwWindowShouldClose(pWindow)) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;

            g_game.update(duration);

            glClear(GL_COLOR_BUFFER_BIT);

            g_game.render();

            glfwSwapBuffers(pWindow);
            glfwPollEvents();
        }

        ResourceManager::unloadResources();
    }

    glfwTerminate();
    return 0;
}