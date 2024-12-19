#include "Level.h"

#include "./GameObjects/BrickWall.h"
#include "iostream"
#include "memory"
#include "GameObjects/ConcreteWall.h"
#include "GameObjects/Trees.h"
#include "GameObjects/Ice.h"
#include "GameObjects/Water.h"
#include "GameObjects/Eagle.h"

u_int BLOCK_SIZE = 16;

// Todo: refactor - create factory class
std::shared_ptr<GameObject> createGameObjectFromDescription(
        const char &description,
        const glm::vec2 &position,
        const glm::vec2 &size
) {
    switch (description) {
        case '0':
            return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Right, position, size);
        case '1':
            return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Bottom, position, size);
        case '2':
            return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Left, position, size);
        case '3':
            return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Top, position, size);
        case '4':
            return std::make_shared<BrickWall>(BrickWall::EBrickWallType::All, position, size);
        case 'G':
            return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomLeft, position, size);
        case 'H':
            return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomRight, position, size);
        case 'I':
            return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopLeft, position, size);
        case 'J':
            return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopRight, position, size);


        case '5':
            return std::make_shared<ConcreteWall>(ConcreteWall::EConcreteWallType::Right, position, size);
        case '6':
            return std::make_shared<ConcreteWall>(ConcreteWall::EConcreteWallType::Bottom, position, size);
        case '7':
            return std::make_shared<ConcreteWall>(ConcreteWall::EConcreteWallType::Left, position, size);
        case '8':
            return std::make_shared<ConcreteWall>(ConcreteWall::EConcreteWallType::Top, position, size);
        case '9':
            return std::make_shared<ConcreteWall>(ConcreteWall::EConcreteWallType::All, position, size);

        case 'B':
            return std::make_shared<Trees>(position, size);
        case 'C':
            return std::make_shared<Ice>(position, size);
        case 'A':
            return std::make_shared<Water>(position, size);


        case 'E':
            return std::make_shared<Eagle>(position, size);

        case 'D':
            return nullptr;
        default:
            std::cerr << "Unknown GameObject description: " << description << std::endl;
            return nullptr;
    }
};

Level::Level(const std::vector<std::string> &levelDescription) {
    if (levelDescription.empty()) {
        std::cerr << "Empty level description!" << std::endl;
        return;
    }

    m_width = levelDescription[0].length();
    m_height = levelDescription.size();

    m_mapObjects.reserve(m_width * m_height);

    u_int currentBottomOffset = BLOCK_SIZE * (m_height - 1);
    for (const std::string &currentRow: levelDescription) {
        u_int currentLeftOffset = 0;

        for (const char currentElement: currentRow) {
            const auto gameObject = createGameObjectFromDescription(
                    currentElement,
                    glm::vec2(currentLeftOffset, currentBottomOffset),
                    glm::vec2(BLOCK_SIZE, BLOCK_SIZE)
            );
            m_mapObjects.emplace_back(gameObject);

            currentLeftOffset += BLOCK_SIZE;
        }

        currentBottomOffset -= BLOCK_SIZE;
    }
}

void Level::render() const {
    for (const auto &currentMapObject: m_mapObjects) {
        if (currentMapObject) {
            currentMapObject->render();
        }
    }
}

void Level::update(uint64_t delta) {
    for (const auto &currentMapObject: m_mapObjects) {
        if (currentMapObject) {
            currentMapObject->update(delta);
        }
    }
}
