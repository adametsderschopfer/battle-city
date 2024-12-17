#pragma once

#include "array"
#include "memory"

#include "../../Core/GameObject.h"

namespace RenderEngine {
    class Sprite;
}

class BrickWall : public GameObject {
public:
    enum class EBrickWallType {
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

    enum class EBrickState {
        All = 0,
        TopLeft,
        TopRight,
        Top,
        BottomLeft,
        Left,
        TopRight_BottomLeft,
        Top_BottomLeft,
        BottomRight,
        TopLeft_BottomRight,
        Right,
        Top_BottomRight,
        Bottom,
        TopLeft_Bottom,
        TopRight_Bottom,
        Destroyed
    };

    enum class EBrickLocation {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
    };

    BrickWall(
            const EBrickWallType &eBrickWallType,
            const glm::vec2 &position,
            const glm::vec2 &size,
            const float &rotation = 0.f
    );

    void render() const override;

    void update(uint64_t delta) override;

private:
    std::array<EBrickState, 4> m_eCurrentBrickState;
    std::array<std::shared_ptr<RenderEngine::Sprite>, 15> m_sprites;

    void renderBrick(const EBrickLocation &eBrickLocation) const;
};
