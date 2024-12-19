#pragma once

#include "array"
#include "memory"

#include "../../Core/GameObject.h"

namespace RenderEngine {
    class Sprite;
}

class Trees : public GameObject {
public:
    enum class EBlockLocation : uint8_t {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
    };

    Trees(
            const glm::vec2 &position,
            const glm::vec2 &size,
            const float &rotation = 0.f
    );

    void render() const override;

private:
    std::shared_ptr<RenderEngine::Sprite> m_sprite;
    std::array<glm::vec2, 4> m_blockOffsets;

    void renderBlock(const EBlockLocation &eBlockLocation) const;
};
