#include "Entity.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

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
    // Scrambled data
    std::vector<glm::vec3> verticesArray;
    std::vector<glm::ivec3> indiciesArray;
    std::vector<glm::vec2> textureCoordsArray;
    std::vector<glm::vec3> normalsArray;

    // Unscrambled data
    std::vector<float> vertices;
    std::vector<GLuint> indicies;
    std::vector<float> textureCoords;
    std::vector<float> normals;

    std::ifstream reader(obj_path + ".obj");
    if (reader.fail())
    {
        std::cout << "Could not load OBJ by the name of " << obj_path << ".obj" << std::endl;
    }
    else
    {
        std::string line;
        while (!reader.eof())
        {
            // Get the next line
            std::getline(reader, line);

            if (line[0] == 'v' && line[1] == ' ') // vertices
            {
                // Erase the v
                line.erase(0, 1);

                // Make a istringstream and it can convert to numbers
                std::istringstream iss(line);

                // Number type
                float value;

                // Push the vertex into the verticesArray
                iss >> value;
                float x = value;
                iss >> value;
                float y = value;
                iss >> value;
                float z = value;

                verticesArray.push_back({ x, y, z });
            }
            else if (line[0] == 'v' && line[1] == 't')   // texture coords
            {
                line.erase(0, 2);
                std::istringstream iss(line);

                float value;

                iss >> value;
                float x = value;
                iss >> value;
                float y = value;

                textureCoordsArray.push_back({ x, y });
            }
            else if (line[0] == 'v' && line[1] == 'n')   // normals
            {
                line.erase(0, 2);
                std::istringstream iss(line);

                float value;

                iss >> value;
                float x = value;
                iss >> value;
                float y = value;
                iss >> value;
                float z = value;

                normalsArray.push_back({ x, y, z });
            }
            else if (line[0] == 'f')    // faces aka triangles
            {
                // Replace every \ with a space
                std::replace(line.begin(), line.end(), '/', ' ');

                line.erase(0, 1);
                std::istringstream iss(line);

                int value;

                for (int i = 0; i < 3; i++)
                {
                    iss >> value;
                    int x = value;
                    iss >> value;
                    int y = value;
                    iss >> value;
                    int z = value;

                    indiciesArray.push_back({ x, y, z });
                }
            }
            else continue;
        }

        // Each vertex has a texture coordinate
        textureCoords = std::vector<float>(verticesArray.size() * 2, -1);

        // Each vertex also has normal
        normals = std::vector<float>(verticesArray.size() * 3, -1);

        // Order the data using the faces data
        for (int i = 0; i < (int)indiciesArray.size(); i++)
        {
            // Blender start from 1 instead of 0
            int currentVertexIndex = indiciesArray.at(i).x - 1;

            // indicies
            indicies.push_back(currentVertexIndex);

            // textures
            // textures start from bottom left so we have to 1 - the y direction
            int currentTexIndex = indiciesArray.at(i).y - 1;
            glm::vec2 tex = textureCoordsArray.at(currentTexIndex);

            textureCoords.at(currentVertexIndex * 2) = tex.x;
            textureCoords.at(currentVertexIndex * 2 + 1) = 1 - tex.y;

            // normals
            int currentNormalIndex = indiciesArray.at(i).z - 1;
            glm::vec3 norm = normalsArray.at(currentNormalIndex);

            normals.at(currentNormalIndex * 3) = norm.x;
            normals.at(currentNormalIndex * 3 + 1) = norm.y;
            normals.at(currentNormalIndex * 3 + 2) = norm.z;
        }

        // vertices don't have to be ordered since we are using indicies to represent them
        for (int i = 0; i < (int)(verticesArray.size()); i++)
        {
            vertices.push_back(verticesArray.at(i).x);
            vertices.push_back(verticesArray.at(i).y);
            vertices.push_back(verticesArray.at(i).z);
        }
    }

    m_mesh = std::make_unique<Mesh>(vertices, indicies);
    m_mesh->addTexture(texture_path, textureCoords);
}
