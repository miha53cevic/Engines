#pragma once
#include "Mesh.h"
#include <glm/glm.hpp>

class Entity
{
public:
    Entity(Mesh* mesh, glm::vec3 position = {0,0,0}, glm::vec3 rotation = { 0,0,0 }, glm::vec3 scale = { 1,1,1 })
    {
        m_mesh     = mesh;
        m_position = position;
        m_rotation = rotation;
        m_scale    = scale;
    }

    void Move(float dx, float dy, float dz)
    {
        m_position.x += dx;
        m_position.y += dy;
        m_position.z += dz;
    }

    void Rotate(float dx, float dy, float dz)
    {
        m_rotation.x += dx;
        m_rotation.y += dy;
        m_rotation.z += dz;
    }

    void setPosition(glm::vec3 position) { m_position = position; }
    void setRotation(glm::vec3 rotation) { m_rotation = rotation; }
    void setScale(glm::vec3 scale)       { m_scale = scale;       }

    Mesh* getMesh()         { return m_mesh;     }
    glm::vec3 getPosition() { return m_position; }
    glm::vec3 getRotation() { return m_rotation; }
    glm::vec3 getScale()    { return m_scale;    }

private:
    Mesh* m_mesh;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};

