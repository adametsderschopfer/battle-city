#pragma once

#include "glad/glad.h"
#include "glm/vec2.hpp"

#include "memory"
#include "string"

namespace RenderEngine {
    class Texture2D;

    class ShaderProgram;

    class Sprite {
    public:
        Sprite(
                const std::shared_ptr<Texture2D> &pTexture,
                const std::string &initialSubTextureName,
                const std::shared_ptr<ShaderProgram> &pShaderProgram,
                const glm::vec2 &position = glm::vec2(0.f),
                const glm::vec2 &size = glm::vec2(1.f),
                const float &rotation = 0.f
        );

        virtual ~Sprite();

        Sprite(const Sprite &) = delete;

        Sprite &operator=(const Sprite &) = delete;

        virtual void render() const;

        virtual void setPosition(const glm::vec2 &position);

        virtual void setSize(const glm::vec2 &size);

        virtual void setRotation(float rotation);

    protected:
        std::shared_ptr<Texture2D> m_pTexture;
        std::shared_ptr<ShaderProgram> m_pShaderProgram;

        glm::vec2 m_size{};
        glm::vec2 m_position{};
        float m_rotation{};

        GLuint m_VAO{};
        GLuint m_vertexCoordsVBO{};
        GLuint m_textureCoordsVBO{};
    };
}

