#pragma once

#include "glm/vec2.hpp"
#include "memory"
#include "../../Core/GameObject.h"

namespace RenderEngine {
    class AnimatedSprite;
}

class Tank : public GameObject {
public:
    enum class EOrientation {
        Top,
        Bottom,
        Left,
        Right,
    };

    Tank(
            std::shared_ptr<RenderEngine::AnimatedSprite> &pSprite,
            const float &velocity,
            const glm::vec2 &position,
            const glm::vec2 &size,
            const float &rotation = 0.f
    );

    void render() const override;

    void update(uint64_t delta) override;

    void setOrientation(const EOrientation &eOrientation);

    void move(const bool &move);


private:
    EOrientation m_eOrientation;
    std::shared_ptr<RenderEngine::AnimatedSprite> m_pSprite;
    bool m_move;
    float m_velocity;
    glm::vec2 m_moveOffset;
};

