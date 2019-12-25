#include "Entity.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "OBJ_Loader.h"

Entity::Entity(MeshRef mesh, glm::vec3 position, glm::vec3 rotation, float scale)
{
    m_mesh = std::move(mesh);
    m_position = position;
    m_rotation = rotation;
    m_scale = scale;
}

Entity::Entity(std::string obj_path, std::string texture_path, glm::vec3 position, glm::vec3 rotation, float scale)
{
    loadOBJ(obj_path, texture_path);
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

void Entity::loadOBJ(std::string obj_path, std::string texture_path)
{
    // objl loader take from github
    // https://github.com/Bly7/OBJ-Loader
    objl::Loader loader;
    loader.LoadFile(obj_path + ".obj");
    
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indicies;
    std::vector<GLfloat> textureCoords;
    std::vector<GLfloat> normals;

    for (auto& vertex : loader.LoadedMeshes[0].Vertices)
    {
        vertices.push_back(vertex.Position.X);
        vertices.push_back(vertex.Position.Y);
        vertices.push_back(vertex.Position.Z);

        // Napomena mora biti 1.0f - texY inace ne radi
        textureCoords.push_back(vertex.TextureCoordinate.X);
        textureCoords.push_back(1.0f - vertex.TextureCoordinate.Y);

        normals.push_back(vertex.Normal.X);
        normals.push_back(vertex.Normal.Y);
        normals.push_back(vertex.Normal.Z);
    }

    for (auto& indicie : loader.LoadedMeshes[0].Indices)
    {
        indicies.push_back(indicie);
    }

    m_mesh = std::make_unique<Mesh>(vertices, indicies);
    m_mesh->addTexture(texture_path, textureCoords);
    m_mesh->addNormals(normals);
}
