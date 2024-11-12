#pragma once

#include "iostream"
#include "glad/glad.h"

namespace RenderEngine {
    class ShaderProgram {
    public:
        ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader);

        ~ShaderProgram();

        ShaderProgram() = delete;

        ShaderProgram(ShaderProgram &) = delete;

        ShaderProgram &operator=(const ShaderProgram &) = delete;

        ShaderProgram &operator=(ShaderProgram &&shaderProgram) noexcept;

        ShaderProgram(ShaderProgram &&shaderProgram) noexcept;

        [[nodiscard]] bool isCompiled() const {
            return m_isCompiled;
        };

        void setUniformInt(const std::string &name, GLint value);

        void use() const;

    private:
        bool m_isCompiled = false;
        GLuint m_ID = 0;

        static bool createShader(const std::string &source, GLenum shaderType, GLuint &shaderID);
    };
}
