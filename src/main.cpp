#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "iostream"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"
#include "Resources/ResourceManager.h"

glm::ivec2 g_windowSize(1024, 720);

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

    std::cout << "RenderEngine: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(1, 1, 0, 1);

    {
        ResourceManager resourceManager(argv[0]);

        auto pSpriteShaderProgram = resourceManager.loadShaders(
                "SpriteShader",
                "res/shaders/sprite/vSprite.vert",
                "res/shaders/sprite/fSprite.frag"
        );
        if (!pSpriteShaderProgram) {
            std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
            return -1;
        }

        auto tex = resourceManager.loadTexture(
                "DefaultTexture",
                "res/textures/example/map_16x16.png"
        );

        std::vector<std::string> subTextureNames = {
                "fullBricks",
                "topBricks",
                "bottomBricks",
                "leftBricks",
                "rightBricks",
                "topLeftBrick",
                "topRightBrick",
                "bottomLeftBrick",
                "bottomRightBrick",
                "fullConcrete",
        };

        auto pTextureAtlas = resourceManager.loadTextureAtlas(
                "DefaultTextureAtlas",
                "res/textures/example/map_16x16.png",
                subTextureNames,
                16,
                16
        );

        auto pSprite = resourceManager.loadSprite(
                "NewSprite",
                "DefaultTextureAtlas",
                "SpriteShader",
                50, 50,
                "fullConcrete"
        );
        pSprite->setPosition(glm::vec2(300, 100));

        glm::mat4 projectionMatrix = glm::ortho(
                0.f,
                static_cast<float>(g_windowSize.x),
                0.f,
                static_cast<float>(g_windowSize.y),
                -100.f,
                100.f
        );

        pSpriteShaderProgram->use();
        pSpriteShaderProgram->setUniformInt("tex", 0);
        pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        while (!glfwWindowShouldClose(pWindow)) {
            glClear(GL_COLOR_BUFFER_BIT);

            pSprite->render();

            glfwSwapBuffers(pWindow);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}