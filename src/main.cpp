#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "iostream"

#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Resources/ResourceManager.h"

int g_windowSizeX = 1024;
int g_windowSizeY = 720;

GLfloat point[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
};

GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
};

GLfloat textureCoords[] = {
        0.5f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
};

void glfwWindowSizeCallback(GLFWwindow *pWindow, int width, int height) {
    g_windowSizeX = width;
    g_windowSizeY = height;

    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
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
            g_windowSizeX,
            g_windowSizeY,
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
        auto pDefaultShaderProgram = resourceManager.loadShaders(
                "TriangleShader",
                "res/shaders/texture/texture.vert",
                "res/shaders/texture/texture.frag"
        );
        if (!pDefaultShaderProgram) {
            std::cerr << "Can't create shader program: " << "TriangleShader" << std::endl;
            return -1;
        }

        auto tex = resourceManager.loadTexture("test", "res/textures/example/map_16x16.png");

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint texCoord_vbo = 0;
        glGenBuffers(1, &texCoord_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setUniformInt("tex", 0);

        while (!glfwWindowShouldClose(pWindow)) {
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(vao);

            tex->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(pWindow);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}