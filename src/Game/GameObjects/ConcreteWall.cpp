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
    m_eCurrentConcreteState{
            EConcreteState::Destroyed,
            EConcreteState::Destroyed,
            EConcreteState::Destroyed,
            EConcreteState::Destroyed
    },
    m_sprite(ResourceManager::getSprite("betonWall")) {
    switch (eConcreteWallType) {
        case EConcreteWallType::All:
            m_eCurrentConcreteState.fill(EConcreteState::Enabled);
            break;
        case EConcreteWallType::Top:
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::TopLeft)] = EConcreteState::Enabled;
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::TopRight)] = EConcreteState::Enabled;
            break;
        case EConcreteWallType::Bottom:
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::BottomLeft)] = EConcreteState::Enabled;
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::BottomRight)] = EConcreteState::Enabled;
            break;
        case EConcreteWallType::Left:
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::TopLeft)] = EConcreteState::Enabled;
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::BottomLeft)] = EConcreteState::Enabled;
            break;
        case EConcreteWallType::Right:
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::TopRight)] = EConcreteState::Enabled;
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::BottomRight)] = EConcreteState::Enabled;
            break;
        case EConcreteWallType::TopLeft:
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::TopLeft)] = EConcreteState::Enabled;
            break;
        case EConcreteWallType::TopRight:
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::TopRight)] = EConcreteState::Enabled;
            break;
        case EConcreteWallType::BottomLeft:
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::BottomLeft)] = EConcreteState::Enabled;
            break;
        case EConcreteWallType::BottomRight:
            m_eCurrentConcreteState[static_cast<size_t>(EConcreteLocation::BottomRight)] = EConcreteState::Enabled;
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

void ConcreteWall::renderConcrete(const EConcreteLocation &eConcreteLocation) const {
    const EConcreteState state = m_eCurrentConcreteState[static_cast<size_t>(eConcreteLocation)];
    if (state == EConcreteState::Destroyed) {
        return;
    }

    m_sprite->render(
            m_position + m_blockOffsets[static_cast<size_t>(eConcreteLocation)],
            m_size / 2.f,
            m_rotation
    );
}

void ConcreteWall::render() const {
    renderConcrete(EConcreteLocation::TopLeft);
    renderConcrete(EConcreteLocation::TopRight);
    renderConcrete(EConcreteLocation::BottomLeft);
    renderConcrete(EConcreteLocation::BottomRight);
}

void ConcreteWall::update(uint64_t delta) {
// empty
}

