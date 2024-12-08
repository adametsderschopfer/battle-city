#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

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
                const std::shared_ptr<ShaderProgram> &pShaderProgram
        );

        virtual ~Sprite();

        Sprite(const Sprite &) = delete;

        Sprite &operator=(const Sprite &) = delete;

        virtual void render(const glm::vec2 &position, const glm::vec2 &size, const float &rotation) const;

    protected:
        std::shared_ptr<Texture2D> m_pTexture;
        std::shared_ptr<ShaderProgram> m_pShaderProgram;

        RenderEngine::VertexArray m_vertexArray;
        RenderEngine::VertexBuffer m_vertexCoordsBuffer;
        RenderEngine::VertexBuffer m_textureCoordsBuffer;
        RenderEngine::IndexBuffer m_indexBuffer;
    };
}

