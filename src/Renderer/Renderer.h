#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

namespace RenderEngine {
    class Renderer {
    public:
        static void draw(
                const RenderEngine::VertexArray &vertexArray,
                const RenderEngine::IndexBuffer &indexBuffer,
                const RenderEngine::ShaderProgram &shaderProgram
        );

        static void setClearColor(float r, float g, float b, float a);

        static void clear();

        static void
        setViewport(unsigned int width, unsigned int height, unsigned int offsetLeft, unsigned int offsetBottom);

    private:

    };
}
