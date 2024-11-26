#pragma once

#include "glad/glad.h"
#include "vector"

namespace Renderer {
    struct VertexBufferLayoutElement {
        GLint count;
        GLenum type;
        GLboolean normalized;
        u_int size;
    };

    class VertexBufferLayout {
    public:
        VertexBufferLayout();

        void reserveElements(size_t count);

        [[nodiscard]]
        GLsizei getStride() const { return m_stride; };

        void addElementLayoutFloat(u_int count, bool normalized);

        [[nodiscard]]
        const std::vector<VertexBufferLayoutElement> &getLayoutElements() const { return m_layoutElements; }

    private:
        std::vector<VertexBufferLayoutElement> m_layoutElements;
        GLsizei m_stride;
    };
}

