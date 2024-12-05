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
        /*
         * TODO: Refactor
         * */

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
    ResourceManager::loadJSONResources("res/resources.json");

    auto pSpriteShaderProgram = ResourceManager::getShaderProgram("SpriteShader");
    if (!pSpriteShaderProgram) {
        std::cerr << "Can't find shader program SpriteShader" << std::endl;
        return false;
    }

    auto pTextureAtlas = ResourceManager::getTexture("MapTextureAtlas");
    if (!pTextureAtlas) {
        std::cerr << "Can't find texture atlas MapTextureAtlas" << std::endl;
        return false;
    }

    auto pTanksTextureAtlas = ResourceManager::getTexture("TanksTextureAtlas");
    if (!pTextureAtlas) {
        std::cerr << "Can't find texture atlas TanksTextureAtlas" << std::endl;
        return false;
    }

//    auto pAnimatedSprite = ResourceManager::loadAnimatedSprite(
//            "NewAnimatedWater",
//            "MapTextureAtlas",
//            "SpriteShader",
//            50, 50,
//            "water1"
//    );
//    pAnimatedSprite->setPosition(glm::vec2(100, 100));
//    std::vector<std::pair<std::string, uint64_t>> waterState;
//    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
//    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
//    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));
//
//    pAnimatedSprite->insertState("waterState", std::move(waterState));
//    pAnimatedSprite->setState("waterState");

    auto pTanksAnimatedSprite = ResourceManager::getAnimatedSprite("TanksAnimatedSprite");
    if (!pTanksAnimatedSprite) {
        std::cerr << "Can't find animated sprite TanksAnimatedSprite" << std::endl;
        return false;
    }

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

    m_pTank = std::make_unique<Tank>(
            pTanksAnimatedSprite,
            0.00000015f,
            glm::vec2(100.f, 100.f)
    );

    return true;
}

