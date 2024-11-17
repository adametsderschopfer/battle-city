#pragma once

#include "string"
#include "memory"
#include "map"

namespace RenderEngine {
    class ShaderProgram;

    class Texture2D;

    class Sprite;
}

class ResourceManager {
public:
    explicit ResourceManager(const std::string &executablePath);

    ~ResourceManager() = default;

    ResourceManager(const ResourceManager &) = delete;

    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager &operator=(ResourceManager &&shaderProgram) = delete;

    ResourceManager(ResourceManager &&shaderProgram) = delete;

    /* --- Shader --- */
    std::shared_ptr<RenderEngine::ShaderProgram>
    loadShaders(const std::string &shaderName, const std::string &vertexPath, const std::string &fragmentPath);

    std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string &shaderName);

    /* --- Texture ---  */
    std::shared_ptr<RenderEngine::Texture2D>
    loadTexture(const std::string &textureName, const std::string &texturePath);

    std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string &textureName);

    /* --- Sprite ---  */
    std::shared_ptr<RenderEngine::Sprite> loadSprite(
            const std::string &spriteName,
            const std::string &textureName,
            const std::string &shaderProgramName,
            unsigned int spriteWidth,
            unsigned int spriteHeight
    );

    std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string &spriteName);

private:
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramMap;
    ShaderProgramMap m_shaderPrograms;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> Texture2DMap;
    Texture2DMap m_textures;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpriteMap;
    SpriteMap m_sprites;

    std::string m_path;

    [[nodiscard]] std::string getFileStringByRelativePath(const std::string &relativeFilePath) const;
};