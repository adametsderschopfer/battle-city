#include "Game.h"
#include "iostream"
#include "chrono"
#include "glm/gtc/matrix_transform.hpp"

#include "Tank.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include "../Resources/ResourceManager.h"

#include <GLFW/glfw3.h>

Game::Game(const glm::ivec2 &windowSize)
        : m_eCurrentGameState(EGameState::Active),
          m_windowSize(windowSize) {
    m_keys.fill(false);
}

Game::~Game() {

}

void Game::render() const {
    if (m_pTank) {
        m_pTank->render();
    }
}

void Game::update(const uint64_t delta) const {
    if (m_pTank) {
        if (m_keys[GLFW_KEY_W]) {
            m_pTank->setOrientation(Tank::EOrientation::Top);
            m_pTank->move(true);
        } else if (m_keys[GLFW_KEY_A]) {
            m_pTank->setOrientation(Tank::EOrientation::Left);
            m_pTank->move(true);
        } else if (m_keys[GLFW_KEY_D]) {
            m_pTank->setOrientation(Tank::EOrientation::Right);
            m_pTank->move(true);
        } else if (m_keys[GLFW_KEY_S]) {
            m_pTank->setOrientation(Tank::EOrientation::Bottom);
            m_pTank->move(true);
        } else {
            m_pTank->move(false);
        }

        m_pTank->update(delta);
    }
}

void Game::setKey(int key, int action) {
    m_keys[key] = action;
}

bool Game::init() {
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


    std::vector<std::string> tanksSubTextureNames = {
            "tankTop1",
            "tankTop2",
            "tankLeft1",
            "tankLeft2",
            "tankBottom1",
            "tankBottom2",
            "tankRight1",
            "tankRight2",
    };

    auto pTanksTextureAtlas = ResourceManager::loadTextureAtlas(
            "TanksTextureAtlas",
            "res/textures/battle-city/tanks.png",
            tanksSubTextureNames,
            16,
            16
    );
    auto pTanksAnimatedSprite = ResourceManager::loadAnimatedSprite(
            "TanksAnimatedSprite",
            "TanksTextureAtlas",
            "SpriteShader",
            50, 50,
            "tankTop1"
    );

    std::vector<std::pair<std::string, uint64_t>> tankTopState;
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("tankTop1", 500000000));
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("tankTop2", 500000000));

    std::vector<std::pair<std::string, uint64_t>> tankLeftState;
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("tankLeft1", 500000000));
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("tankLeft2", 500000000));

    std::vector<std::pair<std::string, uint64_t>> tankBottomState;
    tankBottomState.emplace_back(std::make_pair<std::string, uint64_t>("tankBottom1", 500000000));
    tankBottomState.emplace_back(std::make_pair<std::string, uint64_t>("tankBottom2", 500000000));

    std::vector<std::pair<std::string, uint64_t>> tankRightState;
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("tankRight1", 500000000));
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("tankRight2", 500000000));

    pTanksAnimatedSprite->insertState("tankTopState", std::move(tankTopState));
    pTanksAnimatedSprite->insertState("tankLeftState", std::move(tankLeftState));
    pTanksAnimatedSprite->insertState("tankBottomState", std::move(tankBottomState));
    pTanksAnimatedSprite->insertState("tankRightState", std::move(tankRightState));

    pTanksAnimatedSprite->setState("tankTopState");

    m_pTank = std::make_unique<Tank>(
            pTanksAnimatedSprite,
            0.00000015f,
            glm::vec2(100.f, 100.f)
    );

    return true;
}

