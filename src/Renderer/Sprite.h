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
        struct FrameDescription {
            FrameDescription(
                    glm::vec2 _leftBottomUV,
                    glm::vec2 _rightTopUV,
                    uint64_t _duration
            ) :
                    leftBottomUV(_leftBottomUV),
                    rightTopUV(_rightTopUV),
                    duration(_duration) {};

            glm::vec2 leftBottomUV;
            glm::vec2 rightTopUV;
            uint64_t duration;
        };

        Sprite(
                const std::shared_ptr<Texture2D> &pTexture,
                const std::string &initialSubTextureName,
                const std::shared_ptr<ShaderProgram> &pShaderProgram
        );

        virtual ~Sprite();

        Sprite(const Sprite &) = delete;

        Sprite &operator=(const Sprite &) = delete;

        void render(
                const glm::vec2 &position,
                const glm::vec2 &size,
                const float &rotation,
                size_t frameIdx = 0
        ) const;

        [[nodiscard]]
        uint64_t getFrameDuration(size_t frameIdx) const;

        [[nodiscard]]
        size_t getFramesCount() const;

        void insertFrames(std::vector<FrameDescription> frameDescriptions);

    protected:
        std::shared_ptr<Texture2D> m_pTexture;
        std::shared_ptr<ShaderProgram> m_pShaderProgram;

        RenderEngine::VertexArray m_vertexArray;
        RenderEngine::VertexBuffer m_vertexCoordsBuffer;
        RenderEngine::VertexBuffer m_textureCoordsBuffer;
        RenderEngine::IndexBuffer m_indexBuffer;

        std::vector<FrameDescription> m_frameDescriptions;
        mutable size_t m_lastFrameIdx;
    };
}

