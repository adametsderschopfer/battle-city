#pragma once

#include "memory"

#include "../../Core/GameObject.h"

namespace RenderEngine {
    class Sprite;
}

class BrickWall : public GameObject {
public:
    BrickWall(
            const std::shared_ptr<RenderEngine::Sprite> &pSprite,
            const glm::vec2 &position,
            const glm::vec2 &size,
            const float &rotation = 0.f
    );

    void render() const override;

    void update(uint64_t delta) override;

private:
    std::shared_ptr<RenderEngine::Sprite> m_pCurrentSprite;
};
