#include "VertexArray.h"

Renderer::VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
}

Renderer::VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_id); }

Renderer::VertexArray &Renderer::VertexArray::operator=(Renderer::VertexArray &&vertexArray) noexcept {
    m_id = vertexArray.m_id;
    vertexArray.m_id = 0;
    return *this;
}

Renderer::VertexArray::VertexArray(Renderer::VertexArray &&vertexArray) noexcept {
    m_id = vertexArray.m_id;
    vertexArray.m_id = 0;
}

void Renderer::VertexArray::addBuffer(const Renderer::VertexBuffer &vertexBuffer,
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

void Renderer::VertexArray::bind() const {
    glBindVertexArray(m_id);
}

void Renderer::VertexArray::unbind() const {
    glBindVertexArray(0);
}
