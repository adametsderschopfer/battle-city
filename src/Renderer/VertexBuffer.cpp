#include "VertexBuffer.h"

RenderEngine::VertexBuffer::VertexBuffer()
        : m_id(0) {
}

RenderEngine::VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_id); }

RenderEngine::VertexBuffer &RenderEngine::VertexBuffer::operator=(RenderEngine::VertexBuffer &&vertexBuffer) noexcept {
    m_id = vertexBuffer.m_id;
    vertexBuffer.m_id = 0;
    return *this;
}

RenderEngine::VertexBuffer::VertexBuffer(RenderEngine::VertexBuffer &&vertexBuffer) noexcept {
    m_id = vertexBuffer.m_id;
    vertexBuffer.m_id = 0;
}

void RenderEngine::VertexBuffer::init(const void *data, unsigned int size) {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void RenderEngine::VertexBuffer::update(const void *data, unsigned int size) const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void RenderEngine::VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void RenderEngine::VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}