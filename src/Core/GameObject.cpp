#include "GameObject.h"

GameObject::GameObject(const glm::vec2 &position, const glm::vec2 &size, const float &rotation)
        : m_position(position),
          m_size(size),
          m_rotation(rotation) {

}

GameObject::~GameObject() {

}

void GameObject::GameObject::setPosition(const glm::vec2 &position) {
    m_position = position;
}

void GameObject::GameObject::setSize(const glm::vec2 &size) {
    m_size = size;
}

void GameObject::GameObject::setRotation(const float rotation) {
    m_rotation = rotation;
}