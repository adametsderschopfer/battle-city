#include "Renderer.h"

void
RenderEngine::Renderer::draw(
        const RenderEngine::VertexArray &vertexArray,
        const RenderEngine::IndexBuffer &indexBuffer,
        const RenderEngine::ShaderProgram &shaderProgram
) {
    shaderProgram.use();
    vertexArray.bind();
    indexBuffer.bind();

    glDrawElements(
            GL_TRIANGLES,
            indexBuffer.getCount(),
            GL_UNSIGNED_INT,
            nullptr
    );
}

void RenderEngine::Renderer::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void RenderEngine::Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderEngine::Renderer::setViewport(
        unsigned int width,
        unsigned int height,
        unsigned int offsetLeft,
        unsigned int offsetBottom
) {
    glViewport(
            offsetLeft,
            offsetBottom,
            width,
            height
    );
}
