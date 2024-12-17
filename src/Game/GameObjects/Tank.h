#pragma once

#include "glm/vec2.hpp"
#include "memory"

#include "../../Core/GameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine {
    class Sprite;
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
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;

    RenderEngine::SpriteAnimator m_spriteAnimator_top;
    RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
    RenderEngine::SpriteAnimator m_spriteAnimator_left;
    RenderEngine::SpriteAnimator m_spriteAnimator_right;

    EOrientation m_eOrientation;
    bool m_move;
    float m_velocity;
    glm::vec2 m_moveOffset;
};

