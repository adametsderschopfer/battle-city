#pragma once

#include "array"
#include "memory"

#include "../../Core/GameObject.h"

namespace RenderEngine {
    class Sprite;
}

class ConcreteWall : public GameObject {
public:
    enum class EConcreteWallType {
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

    enum class EConcreteState {
        Enabled = 0,
        Destroyed
    };

    enum class EConcreteLocation {
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
    std::array<EConcreteState, 4> m_eCurrentConcreteState;
    std::shared_ptr<RenderEngine::Sprite> m_sprite;
    std::array<glm::vec2, 4> m_blockOffsets;

    void renderConcrete(const EConcreteLocation &eConcreteLocation) const;
};
