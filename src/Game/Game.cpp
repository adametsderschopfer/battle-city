#include "Game.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "iostream"
#include "chrono"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include "../Resources/ResourceManager.h"

Game::Game(const glm::ivec2 &windowSize)
        : m_eCurrentGameState(EGameState::Active),
          m_windowSize(windowSize) {
    m_keys.fill(false);
}

Game::~Game() {

}

void Game::render() const {
    ResourceManager::getAnimatedSprite("NewAnimatedWater")->render();
}

void Game::update(const uint64_t delta) const {
    ResourceManager::getAnimatedSprite("NewAnimatedWater")->update(delta);
}

void Game::setKey(int key, int action) {
    m_keys[key] = action;
}

bool Game::init() const {
    auto pSpriteShaderProgram = ResourceManager::loadShaders(
            "SpriteShader",
            "res/shaders/sprite/vSprite.vert",
            "res/shaders/sprite/fSprite.frag"
    );
    if (!pSpriteShaderProgram) {
        std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
        return false;
    }

    auto tex = ResourceManager::loadTexture(
            "DefaultTexture",
            "res/textures/example/map_16x16.png"
    );

    std::vector<std::string> subTextureNames = {
            "fullBricks",
            "topBricks",
            "bottomBricks",
            "leftBricks",
            "rightBricks",
            "topLeftBrick",
            "topRightBrick",
            "bottomLeftBrick",
            "bottomRightBrick",

            "fullConcrete",
            "topConcrete",
            "bottomConcrete",
            "leftConcrete",
            "rightConcrete",
            "topLeftConcrete",
            "topRightConcrete",
            "bottomLeftConcrete",
            "bottomRightConcrete",

            "water1",
            "water2",
            "water3",
            "trees",
            "ice",
            "wall",

            "eagle",
            "deadEagle",
            "nothing",

            "respawn1",
            "respawn2",
            "respawn3",
            "respawn4",
    };

    auto pTextureAtlas = ResourceManager::loadTextureAtlas(
            "DefaultTextureAtlas",
            "res/textures/example/map_16x16.png",
            subTextureNames,
            16,
            16
    );

    auto pAnimatedSprite = ResourceManager::loadAnimatedSprite(
            "NewAnimatedWater",
            "DefaultTextureAtlas",
            "SpriteShader",
            50, 50,
            "water1"
    );
    pAnimatedSprite->setPosition(glm::vec2(100, 100));
    std::vector<std::pair<std::string, uint64_t>> waterState;
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));

    pAnimatedSprite->insertState("waterState", std::move(waterState));
    pAnimatedSprite->setState("waterState");

    glm::mat4 projectionMatrix = glm::ortho(
            0.f,
            static_cast<float>(m_windowSize.x),
            0.f,
            static_cast<float>(m_windowSize.y),
            -100.f,
            100.f
    );

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setUniformInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    return true;
}

