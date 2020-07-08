#include "Entity.h"

Entity::Entity()
    : position(0, 0, 0)
    , rotation(0, 0, 0)
    , scale(1, 1, 1)
{
}

Entity::~Entity()
{
}

void Entity::setEBO(const std::vector<GLuint>& indicies, int DrawMode)
{
    VAO.Bind();
    EBO.setData(indicies, DrawMode);
    VAO.Unbind();
}

void Entity::setVBO(const std::vector<GLfloat>& data, int attributeID, int size, int DrawMode)
{
    VAO.Bind();
    auto VBO = std::make_unique<gl::VertexBufferObject>();
    VBO->setData(data, attributeID, size, DrawMode);
    VBOs.push_back(std::move(VBO));
    VAO.Unbind();
}

void Entity::updateEBO(const std::vector<GLuint>& indicies)
{
    VAO.Bind();
    EBO.setSubData(indicies);
    VAO.Unbind();
}

void Entity::updateVBO(const std::vector<GLfloat>& data, int index)
{
    if (index >= VBOs.size())
    {
        printf("Error: VBO at '%d' does not exist!", index);
        return;
    }

    VAO.Bind();
    VBOs[index]->setSubData(data);
    VAO.Unbind();
}

void Entity::draw(int mode, int type, const void * indicies)
{
    VAO.Bind();
    glDrawElements(mode, EBO.size, type, indicies);
    VAO.Unbind();
}