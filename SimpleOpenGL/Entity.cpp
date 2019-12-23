#include "Entity.h"

Entity::Entity(MeshRef mesh, glm::vec3 position, glm::vec3 rotation, float scale)
{
    m_mesh = std::move(mesh);
    m_position = position;
    m_rotation = rotation;
    m_scale = scale;
}

void Entity::Move(float dx, float dy, float dz)
{
    m_position.x += dx;
    m_position.y += dy;
    m_position.z += dz;
}

void Entity::Rotate(float dx, float dy, float dz)
{
    m_rotation.x += dx;
    m_rotation.y += dy;
    m_rotation.z += dz;
}

MeshRef& Entity::getMesh()
{
    return m_mesh;
}

glm::vec3 Entity::getPosition()
{
    return m_position;
}

glm::vec3 Entity::getRotation()
{
    return m_rotation;
}

float Entity::getScale()
{
    return m_scale;
}

void Entity::setMesh(MeshRef mesh)
{
    m_mesh = std::move(mesh);
}

void Entity::setPosition(glm::vec3 position)
{
    m_position = position;
}

void Entity::setRotation(glm::vec3 rotation)
{
    m_rotation = rotation;
}

void Entity::setScale(float scale)
{
    m_scale = scale;
}
