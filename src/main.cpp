#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "iostream"

#include "Renderer/ShaderProgram.h"

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

const char *vertex_shader =
        "#version 410\n"
        "layout(location = 0) in vec3 vertex_position;\n"
        "layout(location = 1) in vec3 vertex_color;\n"
        "out vec3 color;\n"
        "void main(){\n"
        "   color = vertex_color;\n"
        "   gl_Position = vec4(vertex_position, 1.0f);\n"
        "}\0";

const char *fragment_shader =
        "#version 410\n"
        "in vec3 color;\n"
        "out vec4 frag_color;\n"
        "void main(){\n"
        "    frag_color = vec4(color, 1.0f);\n"
        "}\0";

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

int main(void) {
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

    std::string vertexShader(vertex_shader);
    std::string fragmentShader(fragment_shader);

    RenderEngine::ShaderProgram shaderProgram(vertexShader, fragmentShader);
    if (!shaderProgram.isCompiled()) {
        std::cerr << "Can't create shader program!" << std::endl;
        return -1;
    }

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    while (!glfwWindowShouldClose(pWindow)) {
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}