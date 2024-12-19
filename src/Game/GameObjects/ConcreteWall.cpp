#include "ConcreteWall.h"

#include <utility>
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

ConcreteWall::ConcreteWall(
        const EConcreteWallType &eConcreteWallType,
        const glm::vec2 &position,
        const glm::vec2 &size,
        const float &rotation
) : GameObject(position, size, rotation),
    m_eCurrentBlockState{
            EBlockState::Destroyed,
            EBlockState::Destroyed,
            EBlockState::Destroyed,
            EBlockState::Destroyed
    },
    m_sprite(ResourceManager::getSprite("betonWall")) {
    switch (eConcreteWallType) {
        case EConcreteWallType::All:
            m_eCurrentBlockState.fill(EBlockState::Enabled);
            break;
        case EConcreteWallType::Top:
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] = EBlockState::Enabled;
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] = EBlockState::Enabled;
            break;
        case EConcreteWallType::Bottom:
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] = EBlockState::Enabled;
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] = EBlockState::Enabled;
            break;
        case EConcreteWallType::Left:
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] = EBlockState::Enabled;
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] = EBlockState::Enabled;
            break;
        case EConcreteWallType::Right:
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] = EBlockState::Enabled;
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] = EBlockState::Enabled;
            break;
        case EConcreteWallType::TopLeft:
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] = EBlockState::Enabled;
            break;
        case EConcreteWallType::TopRight:
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] = EBlockState::Enabled;
            break;
        case EConcreteWallType::BottomLeft:
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] = EBlockState::Enabled;
            break;
        case EConcreteWallType::BottomRight:
            m_eCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] = EBlockState::Enabled;
            break;

        default:
            break;
    }

    m_blockOffsets = {
            glm::vec2(0, m_size.y / 2.f),
            glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
            glm::vec2(0, 0),
            glm::vec2(m_size.x / 2.f, 0),
    };
}

void ConcreteWall::renderBlock(const EBlockLocation &eBlockLocation) const {
    const EBlockState state = m_eCurrentBlockState[static_cast<size_t>(eBlockLocation)];
    if (state == EBlockState::Destroyed) {
        return;
    }

    m_sprite->render(
            m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)],
            m_size / 2.f,
            m_rotation
    );
}

void ConcreteWall::render() const {
    renderBlock(EBlockLocation::TopLeft);
    renderBlock(EBlockLocation::TopRight);
    renderBlock(EBlockLocation::BottomLeft);
    renderBlock(EBlockLocation::BottomRight);
}

void ConcreteWall::update(uint64_t delta) {
// empty
}

