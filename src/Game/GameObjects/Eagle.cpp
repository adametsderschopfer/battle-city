#include "Eagle.h"

#include <utility>
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Eagle::Eagle(
        const glm::vec2 &position,
        const glm::vec2 &size,
        const float &rotation
) : GameObject(position, size, rotation),
    m_sprites({
                      ResourceManager::getSprite("eagle"),
                      ResourceManager::getSprite("eagle_dead")
              }),
    m_eCurrentState(EEagleState::Alive) {
}

void Eagle::render() const {
    m_sprites[static_cast<size_t>(m_eCurrentState)]->render(
            m_position,
            m_size,
            m_rotation
    );
}

void Eagle::update(uint64_t delta) {

}
