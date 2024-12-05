#pragma once

#include "string"
#include "memory"
#include "map"
#include "vector"

namespace RenderEngine {
    class ShaderProgram;

    class Texture2D;

    class Sprite;

    class AnimatedSprite;
}

class ResourceManager {
public:
    static void setExecutablePath(const std::string &executablePath);

    static void unloadResources();

    ResourceManager() = delete;

    ~ResourceManager() = delete;

    ResourceManager(const ResourceManager &) = delete;

    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager &operator=(ResourceManager &&shaderProgram) = delete;

    ResourceManager(ResourceManager &&shaderProgram) = delete;

    /* --- Shader --- */
    static std::shared_ptr<RenderEngine::ShaderProgram>
    loadShaders(const std::string &shaderName, const std::string &vertexPath, const std::string &fragmentPath);

    static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string &shaderName);

    /* --- Texture ---  */
    static std::shared_ptr<RenderEngine::Texture2D>
    loadTexture(const std::string &textureName, const std::string &texturePath);

    static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string &textureName);

    static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(
            const std::string &textureName,
            const std::string &texturePath,
            const std::vector<std::string> &subTextures,
            unsigned int subTextureWidth,
            unsigned int subTextureHeight
    );

    /* --- Sprite ---  */
    static std::shared_ptr<RenderEngine::Sprite> loadSprite(
            const std::string &spriteName,
            const std::string &textureName,
            const std::string &shaderProgramName,
            unsigned int spriteWidth,
            unsigned int spriteHeight,
            const std::string &subTextureName = "default"
    );

    static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string &spriteName);

    /* --- AnimatedSprite ---  */
    static std::shared_ptr<RenderEngine::AnimatedSprite> loadAnimatedSprite(
            const std::string &spriteName,
            const std::string &textureName,
            const std::string &shaderProgramName,
            unsigned int spriteWidth,
            unsigned int spriteHeight,
            const std::string &subTextureName = "default"
    );

    static std::shared_ptr<RenderEngine::AnimatedSprite> getAnimatedSprite(const std::string &spriteName);

    static bool loadJSONResources(const std::string &JSONPath);

private:
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramMap;
    static ShaderProgramMap m_shaderPrograms;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> Texture2DMap;
    static Texture2DMap m_textures;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpriteMap;
    static SpriteMap m_sprites;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::AnimatedSprite>> AnimatedSpriteMap;
    static AnimatedSpriteMap m_animatedSprites;

    static std::string m_path;

    static std::string getFileStringByRelativePath(const std::string &relativeFilePath);
};