#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"

#include <fstream>
#include <memory>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_ONLY_PNG

#include "stb_image.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

ResourceManager::ShaderProgramMap ResourceManager::m_shaderPrograms;
ResourceManager::Texture2DMap ResourceManager::m_textures;
ResourceManager::SpriteMap ResourceManager::m_sprites;
ResourceManager::AnimatedSpriteMap ResourceManager::m_animatedSprites;
std::string ResourceManager::m_path;
std::vector<const std::vector<std::string>> ResourceManager::m_levels;

std::shared_ptr<RenderEngine::ShaderProgram>
ResourceManager::loadShaders(
        const std::string &shaderName,
        const std::string &vertexPath,
        const std::string &fragmentPath
) {
    if (m_shaderPrograms.contains(shaderName)) {
        std::cerr << "ResourceManager->loadShaders: Shader name \'" + shaderName + "\' already exists" << std::endl;
        return nullptr;
    }

    std::string vertexString = getFileStringByRelativePath(vertexPath);
    if (vertexString.empty()) {
        std::cerr << "ResourceManager->loadShaders [vertexString]: No vertex shader " << std::endl;
        return nullptr;
    }

    std::string fragmentString = getFileStringByRelativePath(fragmentPath);
    if (fragmentString.empty()) {
        std::cerr << "ResourceManager->loadShaders [fragmentString]: No vertex shader " << std::endl;
        return nullptr;
    }

    std::shared_ptr<RenderEngine::ShaderProgram> &newShader = m_shaderPrograms.emplace(
            shaderName,
            std::make_shared<RenderEngine::ShaderProgram>(
                    vertexString,
                    fragmentString
            )
    ).first->second;

    if (!newShader->isCompiled()) {
        std::cerr << "ResourceManager->loadShaders: Can't load shader program: \n"
                  << "\tVertex: " << vertexPath << "\n"
                  << "\tFragment: " << fragmentPath << "\n"
                  << std::endl;

        return nullptr;
    }

    return newShader;
}

std::shared_ptr<RenderEngine::ShaderProgram>
ResourceManager::getShaderProgram(
        const std::string &shaderName
) {
    auto it = m_shaderPrograms.find(shaderName);
    if (it != m_shaderPrograms.end()) {
        return it->second;
    }

    std::cerr << "ResourceManager->getShaderProgram: Can't find shader program by " << shaderName << std::endl;

    return nullptr;
}

std::string
ResourceManager::getFileStringByRelativePath(const std::string &relativeFilePath) {
    std::ifstream f;
    f.open(m_path + "/" + relativeFilePath, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cerr << "ResourceManager->getFileStringByRelativePath: Failed to open file: "
                  << relativeFilePath
                  << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << f.rdbuf();

    return buffer.str();
}

std::shared_ptr<RenderEngine::Texture2D>
ResourceManager::loadTexture(const std::string &textureName, const std::string &texturePath) {
    int channels = 0;
    int width = 0;
    int height = 0;

    stbi_set_flip_vertically_on_load(true);
    unsigned char *pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);
    if (!pixels) {
        std::cerr << "Can't load image: " << texturePath << std::endl;
        return nullptr;
    }

    std::shared_ptr<RenderEngine::Texture2D> &newTexture = m_textures.emplace(
            textureName,
            std::make_shared<RenderEngine::Texture2D>(
                    width,
                    height,
                    pixels,
                    channels,
                    GL_NEAREST,
                    GL_CLAMP_TO_EDGE
            )
    ).first->second;

    stbi_image_free(pixels);

    return newTexture;
}

std::shared_ptr<RenderEngine::Texture2D>
ResourceManager::getTexture(const std::string &textureName) {
    auto it = m_textures.find(textureName);
    if (it != m_textures.end()) {
        return it->second;
    }

    std::cerr << "ResourceManager->getTexture: Can't find texture by " << textureName << std::endl;

    return nullptr;
}

std::shared_ptr<RenderEngine::Sprite>
ResourceManager::loadSprite(
        const std::string &spriteName,
        const std::string &textureName,
        const std::string &shaderProgramName,
        const std::string &subTextureName
) {
    auto pTexture = getTexture(textureName);
    if (!pTexture) {
        std::cerr << "Can't find the texture by " << textureName << "for the sprite" << std::endl;
        return nullptr;
    }

    auto pShaderProgram = getShaderProgram(shaderProgramName);
    if (!pShaderProgram) {
        std::cerr << "Can't find the shaderProgram by " << shaderProgramName << "for the sprite" << std::endl;
        return nullptr;
    }

    auto newSprite = m_sprites.emplace(
            spriteName,
            std::make_shared<RenderEngine::Sprite>(
                    pTexture,
                    subTextureName,
                    pShaderProgram
            )
    ).first->second;

    return newSprite;
}

std::shared_ptr<RenderEngine::Sprite>
ResourceManager::getSprite(const std::string &spriteName) {
    auto it = m_sprites.find(spriteName);
    if (it != m_sprites.end()) {
        return it->second;
    }

    std::cerr << "ResourceManager->getSprite: Can't find sprite by " << spriteName << std::endl;

    return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D>
ResourceManager::loadTextureAtlas(
        const std::string &textureName,
        const std::string &texturePath,
        const std::vector<std::string> &subTextures,
        const unsigned int subTextureWidth,
        const unsigned int subTextureHeight
) {
    /*
     * TODO:
     *  Сейчас текстурный атлас грузится линейно, читая каждую строку со спрайтами
     *  и сопоставляя каждый пройденный элемент с текущим индексом в массиве.
     *  *
     *  Нам нужно в массиве уметь управлять любым элементом атласа и задавать в массиве, название спрайта
     *  координаты спрайта на атласе по X/Y
     *  *
     *  Example:
     *      name: betonBlock
     *      spriteX: 32
     *      spriteY: 32
     *  Y
     *  |
     *  |   |S|
     *  |
     *  —————————————————— X
     *  *
     *  1. Изменить конфиг файл
     *  2. Изменить способ парсинга спрайтов в атласе
     * */

    auto pTexture = loadTexture(textureName, texturePath);
    if (pTexture) {
        unsigned int currentTextureOffsetX = 0;
        unsigned int currentTextureOffsetY = pTexture->height();

        for (const auto &currentSubTextureName: subTextures) {
            glm::vec2 leftBottomUV(
                    static_cast<float>(currentTextureOffsetX) / pTexture->width(),
                    (static_cast<float>(currentTextureOffsetY) - (subTextureHeight)) / pTexture->height()
            );
            glm::vec2 rightTopUV(
                    (static_cast<float>(currentTextureOffsetX) + (subTextureWidth)) / pTexture->width(),
                    static_cast<float>(currentTextureOffsetY) / pTexture->height()
            );

            pTexture->addSubTexture(
                    currentSubTextureName,
                    leftBottomUV,
                    rightTopUV
            );

            currentTextureOffsetX += subTextureWidth;
            if (currentTextureOffsetX >= pTexture->width()) {
                currentTextureOffsetX = 0;
                currentTextureOffsetY -= subTextureHeight;
            }
        }
    }

    return pTexture;
}

std::shared_ptr<RenderEngine::AnimatedSprite>
ResourceManager::loadAnimatedSprite(
        const std::string &spriteName,
        const std::string &textureName,
        const std::string &shaderProgramName,
        const std::string &subTextureName
) {
    auto pTexture = getTexture(textureName);
    if (!pTexture) {
        std::cerr << "Can't find the texture by " << textureName << "for the sprite" << std::endl;
        return nullptr;
    }

    auto pShaderProgram = getShaderProgram(shaderProgramName);
    if (!pShaderProgram) {
        std::cerr << "Can't find the shaderProgram by " << shaderProgramName << "for the sprite" << std::endl;
        return nullptr;
    }

    auto newSprite = m_animatedSprites.emplace(
            spriteName,
            std::make_shared<RenderEngine::AnimatedSprite>(
                    pTexture,
                    subTextureName,
                    pShaderProgram
            )
    ).first->second;

    return newSprite;
}

std::shared_ptr<RenderEngine::AnimatedSprite>
ResourceManager::getAnimatedSprite(const std::string &spriteName) {
    auto it = m_animatedSprites.find(spriteName);
    if (it != m_animatedSprites.end()) {
        return it->second;
    }

    std::cerr << "ResourceManager->getSprite: Can't find animated sprite by " << spriteName << std::endl;

    return nullptr;
}

void ResourceManager::setExecutablePath(const std::string &executablePath) {
    size_t found = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0, found);
}

void ResourceManager::unloadResources() {
    m_shaderPrograms.clear();
    m_textures.clear();
    m_sprites.clear();
    m_animatedSprites.clear();
    m_path.clear();
}

bool ResourceManager::loadJSONResources(const std::string &JSONPath) {
    const std::string rawJsonString = getFileStringByRelativePath(JSONPath);
    if (rawJsonString.empty()) {
        std::cerr << "No JSON resources file" << std::endl;
        return false;
    }

    rapidjson::Document document;
    rapidjson::ParseResult parseResult = document.Parse(rawJsonString.c_str());
    if (!parseResult) {
        std::cerr << "JSON parse error: " << GetParseError_En(parseResult.Code())
                  << "(" << parseResult.Offset() << ")" << std::endl;
        std::cerr << "In JSON file: " << JSONPath << std::endl;
        return false;
    }

    auto shadersIt = document.FindMember("shaders");
    if (shadersIt != document.MemberEnd()) {
        for (const auto &currentShader: shadersIt->value.GetArray()) {
            const std::string name = currentShader["name"].GetString();
            const std::string vertexFilePath = currentShader["vertexFilePath"].GetString();
            const std::string fragmentFilePath = currentShader["fragmentFilePath"].GetString();

            loadShaders(name, vertexFilePath, fragmentFilePath);
        }
    }

    auto textureAtlasesIt = document.FindMember("textureAtlases");
    if (textureAtlasesIt != document.MemberEnd()) {
        for (const auto &currentTextureAtlas: textureAtlasesIt->value.GetArray()) {
            const std::string name = currentTextureAtlas["name"].GetString();
            const std::string filePath = currentTextureAtlas["filePath"].GetString();
            const u_int textureWidth = currentTextureAtlas["width"].GetUint();
            const u_int textureHeight = currentTextureAtlas["height"].GetUint();

            const auto subTexture = currentTextureAtlas["subTexture"].GetObject();
            const u_int subTextureWidth = subTexture["width"].GetUint();
            const u_int subTextureHeight = subTexture["height"].GetUint();

            const auto rawSubTextureItems = subTexture["items"].GetArray();
            std::vector<std::string> subTextures;
            subTextures.reserve(rawSubTextureItems.Size());
            for (const auto &currSubTexture: rawSubTextureItems) {
                subTextures.emplace_back(currSubTexture.GetString());
            }

            auto pTextureAtlas = loadTextureAtlas(
                    name,
                    filePath,
                    subTextures,
                    subTextureWidth,
                    subTextureHeight
            );
        }
    }

    auto spritesIt = document.FindMember("sprites");
    if (spritesIt != document.MemberEnd()) {
        for (const auto &currentAnimatedSprite: spritesIt->value.GetArray()) {
            const std::string name = currentAnimatedSprite["name"].GetString();
            const std::string textureAtlasName = currentAnimatedSprite["textureAtlas"].GetString();
            const std::string shaderName = currentAnimatedSprite["shaderName"].GetString();
            const std::string subTextureName = currentAnimatedSprite["subTextureName"].GetString();

            loadSprite(
                    name,
                    textureAtlasName,
                    shaderName,
                    subTextureName
            );
        }
    }

    auto animatedSpritesIt = document.FindMember("animatedSprites");
    if (animatedSpritesIt != document.MemberEnd()) {
        for (const auto &currentAnimatedSprite: animatedSpritesIt->value.GetArray()) {
            const std::string name = currentAnimatedSprite["name"].GetString();
            const std::string textureAtlasName = currentAnimatedSprite["textureAtlasName"].GetString();
            const std::string shaderName = currentAnimatedSprite["shaderName"].GetString();
            const std::string initialSubTexture = currentAnimatedSprite["initialSubTexture"].GetString();

            auto pAnimatedSprite = loadAnimatedSprite(
                    name,
                    textureAtlasName,
                    shaderName,
                    initialSubTexture
            );
            if (!pAnimatedSprite) {
                continue;
            }

            const auto states = currentAnimatedSprite["states"].GetArray();
            for (const auto &currentState: states) {
                const std::string stateName = currentState["stateName"].GetString();
                const auto frames = currentState["frames"].GetArray();

                std::vector<std::pair<std::string, uint64_t>> objectStates;
                objectStates.reserve(frames.Size());

                for (const auto &currentFrame: frames) {
                    const std::string subTextureName = currentFrame["subTextureName"].GetString();
                    const uint64_t duration = currentFrame["duration"].GetUint();

                    objectStates.emplace_back(
                            subTextureName,
                            duration
                    );
                }

                pAnimatedSprite->insertState(stateName, std::move(objectStates));
            }

        }
    }

    auto levelsIt = document.FindMember("levels");
    if (levelsIt != document.MemberEnd()) {
        for (const auto &currentLevel: levelsIt->value.GetArray()) {
            const auto description = currentLevel["description"].GetArray();
            std::vector<std::string> levelRows;
            levelRows.reserve(description.Size());

            size_t maxLength = 0;

            for (const auto &currentRow: description) {
                levelRows.emplace_back(currentRow.GetString());
                if (maxLength < levelRows.back().length()) {
                    maxLength = levelRows.back().length();
                }
            }

            for (auto &currentRow: levelRows) {
                while (currentRow.length() < maxLength) {
                    // TODO: USE CONSTANT for empty object
                    currentRow.append("D");
                }
            }

            m_levels.emplace_back(std::move(levelRows));
        }
    }

    return true;
}
