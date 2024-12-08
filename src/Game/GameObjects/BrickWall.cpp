#include "BrickWall.h"

#include <utility>
#include "../../Renderer/Sprite.h"

BrickWall::BrickWall(
        const std::shared_ptr<RenderEngine::Sprite> &pSprite,
        const glm::vec2 &position,
        const glm::vec2 &size,
        const float &rotation
) : GameObject(position, size, rotation),
    m_pCurrentSprite(pSprite) {
}

void BrickWall::render() const {
    m_pCurrentSprite->render(m_position, m_size, m_rotation);
}

void BrickWall::update(uint64_t delta) {
// empty
}

