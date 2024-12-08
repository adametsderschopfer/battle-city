#include "Tank.h"

#include "../../Renderer/Sprite.h"

Tank::Tank(
        std::shared_ptr<RenderEngine::Sprite> pSprite_top,
        std::shared_ptr<RenderEngine::Sprite> pSprite_bottom,
        std::shared_ptr<RenderEngine::Sprite> pSprite_left,
        std::shared_ptr<RenderEngine::Sprite> pSprite_right,

        const float &velocity,
        const glm::vec2 &position,
        const glm::vec2 &size,
        const float &rotation
) : GameObject(position, size, rotation),

    m_pSprite_top(pSprite_top),
    m_pSprite_bottom(pSprite_bottom),
    m_pSprite_left(pSprite_left),
    m_pSprite_right(pSprite_right),
    m_spriteAnimator_top(m_pSprite_top),
    m_spriteAnimator_bottom(m_pSprite_bottom),
    m_spriteAnimator_left(m_pSprite_left),
    m_spriteAnimator_right(m_pSprite_right),

    m_velocity(velocity),
    m_moveOffset(glm::vec2(0.f, 1.f)),
    m_eOrientation(EOrientation::Top),
    m_move(false) {
}

void Tank::render() const {
    switch (m_eOrientation) {
        case EOrientation::Top:
            m_pSprite_top->render(m_position, m_size, m_rotation, m_spriteAnimator_top.getCurrentFrame());
            break;
        case EOrientation::Right:
            m_pSprite_right->render(m_position, m_size, m_rotation, m_spriteAnimator_right.getCurrentFrame());
            break;
        case EOrientation::Bottom:
            m_pSprite_bottom->render(m_position, m_size, m_rotation, m_spriteAnimator_bottom.getCurrentFrame());
            break;
        case EOrientation::Left:
            m_pSprite_left->render(m_position, m_size, m_rotation, m_spriteAnimator_left.getCurrentFrame());
            break;
    }
}

void Tank::update(const uint64_t delta) {
    if (!m_move) {
        return;
    }

    m_position += static_cast<float>(delta) * m_velocity * m_moveOffset;

    switch (m_eOrientation) {
        case EOrientation::Top:
            m_spriteAnimator_top.update(delta);
            break;
        case EOrientation::Right:
            m_spriteAnimator_right.update(delta);
            break;
        case EOrientation::Bottom:
            m_spriteAnimator_bottom.update(delta);
            break;
        case EOrientation::Left:
            m_spriteAnimator_left.update(delta);
            break;
    }
}

void Tank::setOrientation(const Tank::EOrientation &eOrientation) {
    if (m_eOrientation == eOrientation) {
        return;
    }

    m_eOrientation = eOrientation;

    switch (m_eOrientation) {
        case EOrientation::Top:
            m_moveOffset.x = 0.f;
            m_moveOffset.y = 1.f;
            break;
        case EOrientation::Right:
            m_moveOffset.x = 1.f;
            m_moveOffset.y = 0.f;
            break;
        case EOrientation::Bottom:
            m_moveOffset.x = 0.f;
            m_moveOffset.y = -1.f;
            break;
        case EOrientation::Left:
            m_moveOffset.x = -1.f;
            m_moveOffset.y = 0.f;
            break;
    }
}

void Tank::move(const bool &move) {
    m_move = move;
}
