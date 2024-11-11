#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <fstream>
#include <memory>
#include <sstream>
#include "iostream"

ResourceManager::ResourceManager(const std::string &executablePath) {
    size_t found = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0, found);
}

std::shared_ptr<RenderEngine::ShaderProgram>
ResourceManager::loadShaders(
        const std::string &shaderName,
        const std::string &vertexPath,
        const std::string &fragmentPath
) {
    if (m_shaderPrograms.contains(shaderName)) {
        std::cerr << "ResourceManager::loadShaders: Shader name \'" + shaderName + "\' already exists" << std::endl;
        return nullptr;
    }

    std::string vertexString = getFileStringByRelativePath(vertexPath);
    if (vertexString.empty()) {
        std::cerr << "ResourceManager::loadShaders [vertexString]: No vertex shader " << std::endl;
        return nullptr;
    }

    std::string fragmentString = getFileStringByRelativePath(vertexPath);
    if (fragmentString.empty()) {
        std::cerr << "ResourceManager::loadShaders [fragmentString]: No vertex shader " << std::endl;
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
        std::cerr << "ResourceManager::loadShaders: Can't load shader program: \n"
                  << "\tVertex: " << vertexPath << "\n"
                  << "\tFragment: " << fragmentPath << "\n"
                  << std::endl;

        return nullptr;
    }

    return newShader;
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::getShaderProgram(
        const std::string &shaderName
) {
    auto it = m_shaderPrograms.find(shaderName);
    if (it != m_shaderPrograms.end()) {
        return it->second;
    }

    std::cerr << "ResourceManager::getShaderProgram: Can't find shader program by - " << shaderName << std::endl;

    return nullptr;
}

std::string ResourceManager::getFileStringByRelativePath(const std::string &relativeFilePath) const {
    std::ifstream f;
    f.open(m_path + "/" + relativeFilePath, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cerr << "ResourceManager::getFileStringByRelativePath: Failed to open file: "
                  << relativeFilePath
                  << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << f.rdbuf();

    return buffer.str();
}
