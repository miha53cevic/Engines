#pragma once
#include "Mesh.h"
#include <glm/glm.hpp>

class Entity
{
public:
    Entity(MeshRef mesh, glm::vec3 position, glm::vec3 rotation, float scale);

    void Move(float dx, float dy, float dz);
    void Rotate(float dx, float dy, float dz);

    MeshRef& getMesh();
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    float getScale();

    void setMesh(MeshRef mesh);
    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(float scale);

private:
    MeshRef m_mesh;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    float m_scale;
};

typedef std::unique_ptr<Entity> EntityRef;

