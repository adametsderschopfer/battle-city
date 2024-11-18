#pragma once

#include "glad/glad.h"
#include "glm/vec2.hpp"
#include "iostream"
#include "map"

namespace RenderEngine {
    struct SubTexture2D {
        glm::vec2 leftBottomUV;
        glm::vec2 rightTopUV;

        SubTexture2D(
                const glm::vec2 _leftBottomUV,
                const glm::vec2 _rightTopUV
        ) : leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV) {}


        SubTexture2D(
        ) : leftBottomUV(0.f), rightTopUV(1.f) {}
    };

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

        [[nodiscard]] unsigned int width() const { return m_width; }

        [[nodiscard]] unsigned int height() const { return m_height; }

        static void unbind();

        void bind() const;

        void addSubTexture(std::string name, glm::vec2 leftBottomUV, glm::vec2 rightTopUV);

        [[nodiscard]] const SubTexture2D &getSubTexture(const std::string &name) const;

    private:
        GLuint m_ID{};
        unsigned int m_width;
        unsigned int m_height;

        GLint m_mode;

        std::map<std::string, SubTexture2D> m_subTextures;
    };
}

