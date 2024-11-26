#include "IndexBuffer.h"

RenderEngine::IndexBuffer::IndexBuffer()
        : m_id(0),
          m_count(0) {
}

RenderEngine::IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_id); }

RenderEngine::IndexBuffer &RenderEngine::IndexBuffer::operator=(RenderEngine::IndexBuffer &&indexBuffer) noexcept {
    m_id = indexBuffer.m_id;
    m_count = indexBuffer.m_count;

    indexBuffer.m_id = 0;
    indexBuffer.m_count = 0;

    return *this;
}

RenderEngine::IndexBuffer::IndexBuffer(RenderEngine::IndexBuffer &&indexBuffer) noexcept {
    m_id = indexBuffer.m_id;
    m_count = indexBuffer.m_count;

    indexBuffer.m_id = 0;
    indexBuffer.m_count = 0;
}

void RenderEngine::IndexBuffer::init(const void *data, unsigned int count) {
    m_count = count;

    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

void RenderEngine::IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void RenderEngine::IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}