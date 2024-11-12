#pragma once

#include "glad/glad.h"
#include "string"

namespace RenderEngine {
    class Texture2D {
    public:
        Texture2D(
                GLsizei width,
                GLsizei height,
                const unsigned char *data,
                unsigned int channels,
                GLint filter,
                GLint wrapMode
        );

        ~Texture2D();

        Texture2D() = delete;

        Texture2D(const Texture2D &) = delete;

        Texture2D &operator=(const Texture2D &) = delete;

        Texture2D &operator=(Texture2D &&texture2d) noexcept;

        Texture2D(Texture2D &&texture2d) noexcept;

        static void unbind();

        void bind() const;

    private:
        GLuint m_ID{};
        GLint m_mode;
        GLsizei m_width;
        GLsizei m_height;
    };
}

