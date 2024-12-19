#pragma once

#include "array"
#include "memory"

#include "../../Core/GameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine {
    class Sprite;
}

class Water : public GameObject {
public:
    enum class EBlockLocation : uint8_t {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
    };

    Water(
            const glm::vec2 &position,
            const glm::vec2 &size,
            const float &rotation = 0.f
    );

    void render() const override;

    void update(uint64_t delta) override;

private:
    std::shared_ptr<RenderEngine::Sprite> m_sprite;
    RenderEngine::SpriteAnimator m_spriteAnimator;
    std::array<glm::vec2, 4> m_blockOffsets;

    void renderBlock(const EBlockLocation &eBlockLocation) const;
};
