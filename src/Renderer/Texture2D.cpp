#include "Texture2D.h"
#include "glm/vec2.hpp"

RenderEngine::Texture2D::Texture2D(
        GLsizei width,
        GLsizei height,
        const unsigned char *data,
        unsigned int channels,
        GLint filter,
        GLint wrapMode
) : m_width(width), m_height(height) {
    switch (channels) {
        case 4:
        default:
            m_mode = GL_RGBA;
            break;

        case 3:
            m_mode = GL_RGB;
            break;
    }

    glGenTextures(1, &m_ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            m_mode,
            static_cast<GLsizei>(m_width),
            static_cast<GLsizei>(m_height),
            0,
            m_mode,
            GL_UNSIGNED_BYTE,
            data
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

RenderEngine::Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_ID);
}

RenderEngine::Texture2D &RenderEngine::Texture2D::operator=(RenderEngine::Texture2D &&texture2d) noexcept {
    glDeleteTextures(1, &m_ID);

    m_ID = texture2d.m_ID;
    texture2d.m_ID = 0;
    m_mode = texture2d.m_mode;
    m_width = texture2d.m_width;
    m_height = texture2d.m_height;

    return *this;
}

RenderEngine::Texture2D::Texture2D(RenderEngine::Texture2D &&texture2d) noexcept {
    m_ID = texture2d.m_ID;
    texture2d.m_ID = 0;
    m_mode = texture2d.m_mode;
    m_width = texture2d.m_width;
    m_height = texture2d.m_height;
}

void RenderEngine::Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void RenderEngine::Texture2D::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderEngine::Texture2D::addSubTexture(
        std::string name,
        glm::vec2 leftBottomUV,
        glm::vec2 rightTopUV
) {
    m_subTextures.emplace(name, SubTexture2D(leftBottomUV, rightTopUV));
}

const RenderEngine::SubTexture2D &
RenderEngine::Texture2D::getSubTexture(const std::string &name) const {
    auto it = m_subTextures.find(name);
    if (it != m_subTextures.end()) {
        return it->second;
    }

    const static SubTexture2D defaultSubTexture2D;
    return defaultSubTexture2D;
}
