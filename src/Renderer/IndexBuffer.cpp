#include "IndexBuffer.h"

Renderer::IndexBuffer::IndexBuffer()
        : m_id(0) {
}

Renderer::IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_id); }

Renderer::IndexBuffer &Renderer::IndexBuffer::operator=(Renderer::IndexBuffer &&indexBuffer) noexcept {
    m_id = indexBuffer.m_id;
    indexBuffer.m_id = 0;
    return *this;
}

Renderer::IndexBuffer::IndexBuffer(Renderer::IndexBuffer &&indexBuffer) noexcept {
    m_id = indexBuffer.m_id;
    indexBuffer.m_id = 0;
}

void Renderer::IndexBuffer::init(const void *data, unsigned int size) {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Renderer::IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void Renderer::IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}