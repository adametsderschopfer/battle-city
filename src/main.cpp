#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "iostream"
#include "chrono"
#include "glm/vec2.hpp"

#include "Game/Game.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"

glm::ivec2 g_windowSize(13 * 16, 14 * 16);
std::unique_ptr<Game> g_game = std::make_unique<Game>(g_windowSize);

void glfwWindowSizeCallback(GLFWwindow *pWindow, int width, int height) {
    g_windowSize.x = width;
    g_windowSize.y = height;

    const float level_aspect_ratio = 13.f / 14.f;
    unsigned int viewPortWidth = g_windowSize.x;
    unsigned int viewPortHeight = g_windowSize.y;
    unsigned int viewPortLeftOffset = 0;
    unsigned int viewPortBottomOffset = 0;

    if (static_cast<float>(g_windowSize.x) / g_windowSize.y > level_aspect_ratio) {
        viewPortWidth = static_cast<unsigned int>(g_windowSize.y * level_aspect_ratio);
        viewPortLeftOffset = (g_windowSize.x - viewPortWidth) / 2;
    } else {
        viewPortHeight = static_cast<unsigned int>(g_windowSize.x / level_aspect_ratio);
        viewPortBottomOffset = (g_windowSize.y - viewPortHeight) / 2;
    }

    RenderEngine::Renderer::setViewport(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);
}

void glfwKeyCallback(GLFWwindow *pWindow, int key, int scancode, int action, int mode) {
    g_game->setKey(key, action);
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

    RenderEngine::Renderer::setClearColor(0, 0, 0, 1);
    {
        ResourceManager::setExecutablePath(argv[0]);
        if (!g_game->init()) {
            return -1;
        }

        auto lastTime = std::chrono::high_resolution_clock::now();
        while (!glfwWindowShouldClose(pWindow)) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;

            g_game->update(duration);
            RenderEngine::Renderer::clear();
            g_game->render();

            glfwSwapBuffers(pWindow);
            glfwPollEvents();
        }

        g_game = nullptr;
        ResourceManager::unloadResources();
    }

    glfwTerminate();
    return 0;
}