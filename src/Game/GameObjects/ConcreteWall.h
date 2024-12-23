#pragma once

#include "array"
#include "memory"

#include "../../Core/GameObject.h"

namespace RenderEngine {
    class Sprite;
}

class ConcreteWall : public GameObject {
public:
    enum class EConcreteWallType : uint8_t {
        All,
        Top,
        Bottom,
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    enum class EBlockState : uint8_t {
        Enabled = 0,
        Destroyed
    };

    enum class EBlockLocation : uint8_t {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
    };

    ConcreteWall(
            const EConcreteWallType &eConcreteWallType,
            const glm::vec2 &position,
            const glm::vec2 &size,
            const float &rotation = 0.f
    );

    void render() const override;

    void update(uint64_t delta) override;

private:
    std::array<EBlockState, 4> m_eCurrentBlockState;
    std::shared_ptr<RenderEngine::Sprite> m_sprite;
    std::array<glm::vec2, 4> m_blockOffsets;

    void renderBlock(const EBlockLocation &eBlockLocation) const;
};
