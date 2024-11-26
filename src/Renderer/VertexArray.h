#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "glad/glad.h"

namespace RenderEngine {
    class VertexArray {
    public:
        VertexArray();

        ~VertexArray();

        VertexArray(const VertexArray &) = delete;

        VertexArray &operator=(const VertexArray &) = delete;

        VertexArray &operator=(VertexArray &&vertexArray) noexcept;

        VertexArray(VertexArray &&vertexArray) noexcept;

        void addBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &vertexBufferLayout);

        void bind() const;

        void unbind() const;

    private:
        GLuint m_id = 0;
        u_int m_elementsCount = 0;
    };
}