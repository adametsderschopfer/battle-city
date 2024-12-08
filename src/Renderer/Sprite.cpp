#include "Sprite.h"

#include "ShaderProgram.h"
#include "Texture2D.h"

#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"

RenderEngine::Sprite::Sprite(
        const std::shared_ptr<Texture2D> &pTexture,
        const std::string &initialSubTextureName,
        const std::shared_ptr<ShaderProgram> &pShaderProgram
) : m_pTexture(pTexture),
    m_pShaderProgram(pShaderProgram) {
    const GLfloat vertexCoords[] = {
            // X  Y
            0.f, 0.f,
            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f,
    };

    auto subTexture = m_pTexture->getSubTexture(initialSubTextureName);

    const GLfloat textureCoords[] = {
            // U  V
            subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
            subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
            subTexture.rightTopUV.x, subTexture.rightTopUV.y,
            subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
    };

    const GLuint indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GLfloat));
    RenderEngine::VertexBufferLayout vertexCoordsLayout;
    vertexCoordsLayout.addElementLayoutFloat(2, false);
    m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

    m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GLfloat));
    RenderEngine::VertexBufferLayout textureCoordsLayout;
    textureCoordsLayout.addElementLayoutFloat(2, false);
    m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);

    m_indexBuffer.init(indices, 6);

    m_vertexArray.unbind();
    m_indexBuffer.unbind();
}

RenderEngine::Sprite::~Sprite() {
}

void RenderEngine::Sprite::render(const glm::vec2 &position, const glm::vec2 &size, const float &rotation) const {
    m_pShaderProgram->use();

    /*
     * TODO: Create *Camera* class and move everything for projection, model and other matrix control
     * */

    glm::mat4 model(1.f);

    model = glm::translate(model, glm::vec3(position, 0.f));

    /*Translate origin, rotate and translate back*/
    model = glm::translate(model, glm::vec3(.5f * size.x, .5f * size.y, 0.f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(.0f, 0.f, 1.f));
    model = glm::translate(model, glm::vec3(-.5f * size.x, -.5f * size.y, 0.f));

    model = glm::scale(model, glm::vec3(size, 1.f));

    m_pShaderProgram->setMatrix4("modelMat", model);

    glActiveTexture(GL_TEXTURE0);
    m_pTexture->bind();

    RenderEngine::Renderer::draw(m_vertexArray, m_indexBuffer, *m_pShaderProgram);
}