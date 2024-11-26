#include "VertexBuffer.h"

Renderer::VertexBuffer::VertexBuffer()
        : m_id(0) {
}

Renderer::VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_id); }

Renderer::VertexBuffer &Renderer::VertexBuffer::operator=(Renderer::VertexBuffer &&vertexBuffer) noexcept {
    m_id = vertexBuffer.m_id;
    vertexBuffer.m_id = 0;
    return *this;
}

Renderer::VertexBuffer::VertexBuffer(Renderer::VertexBuffer &&vertexBuffer) noexcept {
    m_id = vertexBuffer.m_id;
    vertexBuffer.m_id = 0;
}

void Renderer::VertexBuffer::init(const void *data, unsigned int size) {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Renderer::VertexBuffer::update(const void *data, unsigned int size) const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void Renderer::VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void Renderer::VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}