#pragma once

#include "vector"
#include "string"
#include "memory"

class GameObject;

class Level {
public:
    Level(const std::vector<std::string> &levelDescription);

    virtual void render() const;

    virtual void update(uint64_t delta);

private:
    u_int m_width;
    u_int m_height;

    std::vector<std::shared_ptr<GameObject>> m_mapObjects;
};

