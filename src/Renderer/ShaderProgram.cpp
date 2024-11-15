#include "ShaderProgram.h"
#include "glm/gtc/type_ptr.hpp"

RenderEngine::ShaderProgram::ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader) {
    GLuint vertexShaderID;
    if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
        std::cerr << "ShaderProgram [ERROR] - vertex shader compile time error" << std::endl;
        return;
    }

    GLuint fragmentShaderID;
    if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
        glDeleteShader(vertexShaderID);

        std::cerr << "ShaderProgram [ERROR] - fragment shader compile time error" << std::endl;
        return;
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShaderID);
    glAttachShader(m_ID, fragmentShaderID);
    glLinkProgram(m_ID);

    GLint success;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        const int bufferSize = 1024;
        GLchar infoLog[bufferSize];
        glGetShaderInfoLog(m_ID, bufferSize, nullptr, infoLog);

        std::cerr << "ShaderProgram [ERROR]: Link time error: \n" << infoLog << std::endl;
    } else {
        m_isCompiled = true;
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

RenderEngine::ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_ID);
}

RenderEngine::ShaderProgram &RenderEngine::ShaderProgram::operator=(ShaderProgram &&shaderProgram) noexcept {
    glDeleteProgram(m_ID);
    m_ID = shaderProgram.m_ID;
    m_isCompiled = shaderProgram.m_isCompiled;

    shaderProgram.m_ID = 0;
    shaderProgram.m_isCompiled = false;

    return *this;
}

RenderEngine::ShaderProgram::ShaderProgram(ShaderProgram &&shaderProgram) noexcept {
    m_ID = shaderProgram.m_ID;
    m_isCompiled = shaderProgram.m_isCompiled;

    shaderProgram.m_ID = 0;
    shaderProgram.m_isCompiled = false;
}

void RenderEngine::ShaderProgram::use() const {
    glUseProgram(m_ID);
}

bool RenderEngine::ShaderProgram::createShader(const std::string &source, const GLenum shaderType, GLuint &shaderID) {
    shaderID = glCreateShader(shaderType);
    const char *pCode = source.c_str();

    glShaderSource(shaderID, 1, &pCode, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (!success) {
        const int bufferSize = 1024;
        GLchar infoLog[bufferSize];
        glGetShaderInfoLog(shaderID, bufferSize, nullptr, infoLog);

        std::cerr << "ShaderProgram [ERROR]: Compile time error: \n" << infoLog << std::endl;

        return false;
    }

    return true;
}

void RenderEngine::ShaderProgram::setUniformInt(const std::string &name, const GLint value) {
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void RenderEngine::ShaderProgram::setMatrix4(const std::string &name, const glm::mat4 &value) {
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
