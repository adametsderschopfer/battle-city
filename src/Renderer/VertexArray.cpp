#include "VertexArray.h"

RenderEngine::VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
}

RenderEngine::VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_id); }

RenderEngine::VertexArray &RenderEngine::VertexArray::operator=(RenderEngine::VertexArray &&vertexArray) noexcept {
    m_id = vertexArray.m_id;
    vertexArray.m_id = 0;
    return *this;
}

RenderEngine::VertexArray::VertexArray(RenderEngine::VertexArray &&vertexArray) noexcept {
    m_id = vertexArray.m_id;
    vertexArray.m_id = 0;
}

void RenderEngine::VertexArray::addBuffer(const RenderEngine::VertexBuffer &vertexBuffer,
                                          const VertexBufferLayout &vertexBufferLayout) {
    bind();
    vertexBuffer.bind();
    const auto &layoutElements = vertexBufferLayout.getLayoutElements();

    GLbyte *offset = nullptr;

    for (u_int i = 0; i < layoutElements.size(); ++i) {
        const auto &currentLayoutElement = layoutElements[i];

        GLuint currentAttribIndex = m_elementsCount + i;

        glEnableVertexAttribArray(currentAttribIndex);
        glVertexAttribPointer(currentAttribIndex, currentLayoutElement.count, currentLayoutElement.type,
                              currentLayoutElement.normalized, vertexBufferLayout.getStride(), offset);

        offset += currentLayoutElement.size;
    }

    m_elementsCount += layoutElements.size();
}

void RenderEngine::VertexArray::bind() const {
    glBindVertexArray(m_id);
}

void RenderEngine::VertexArray::unbind() const {
    glBindVertexArray(0);
}
