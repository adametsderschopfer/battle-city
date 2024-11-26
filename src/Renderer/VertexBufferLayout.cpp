#include "VertexBufferLayout.h"

RenderEngine::VertexBufferLayout::VertexBufferLayout()
        : m_stride(0) {

}

void RenderEngine::VertexBufferLayout::addElementLayoutFloat(u_int count, bool normalized) {
    m_layoutElements.push_back({static_cast<GLint>(count), type: GL_FLOAT, normalized});
    m_stride += static_cast<GLsizei>(m_layoutElements.back().size);
}

void RenderEngine::VertexBufferLayout::reserveElements(const size_t count) {
    m_layoutElements.reserve(count);
}
