#pragma once

#include <cstdint>
#include <array>
#include "glm/ext/vector_int2.hpp"

class Game {
public:
    Game(const glm::ivec2 &windowSize);

    ~Game();

    void render() const;

    void update(uint64_t delta) const;

    void setKey(int key, int action);

    bool init() const;

private:
    glm::ivec2 m_windowSize;

    std::array<bool, 349> m_keys{};

    enum class EGameState {
        Active,
        Pause
    };
    EGameState m_eCurrentGameState;
};