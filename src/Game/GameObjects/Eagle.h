#pragma once

#include "array"
#include "memory"

#include "../../Core/GameObject.h"

namespace RenderEngine {
    class Sprite;
}

class Eagle : public GameObject {
public:
    enum class EEagleState : uint8_t {
        Alive = 0,
        Dead
    };

    Eagle(
            const glm::vec2 &position,
            const glm::vec2 &size,
            const float &rotation = 0.f
    );

    void render() const override;

    void update(uint64_t delta) override;

private:
    std::array<std::shared_ptr<RenderEngine::Sprite>, 2> m_sprites;
    EEagleState m_eCurrentState;
};
