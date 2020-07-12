#include "Entity.h"
#include  "../util/OBJ_Loader.h"

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

void Entity::loadObj(std::string path)
{
    objl::Loader loader;
    if (!loader.LoadFile(path))
    {
        printf("Error: Could not load OBJ");
    }
    auto mesh = loader.LoadedMeshes[0];
    
    std::vector<float> verticies;
    std::vector<float> textureCoords;
    std::vector<float> normals;
    for (int i = 0; i < mesh.Vertices.size(); i++)
    {
        verticies.push_back(mesh.Vertices[i].Position.X);
        verticies.push_back(mesh.Vertices[i].Position.Y);
        verticies.push_back(mesh.Vertices[i].Position.Z);

        textureCoords.push_back(mesh.Vertices[i].TextureCoordinate.X);
        textureCoords.push_back(mesh.Vertices[i].TextureCoordinate.Y);

        normals.push_back(mesh.Vertices[i].Normal.X);
        normals.push_back(mesh.Vertices[i].Normal.Y);
        normals.push_back(mesh.Vertices[i].Normal.Z);
    }

    // Load the VBOs
    setVBO(verticies, 0, 3, GL_STATIC_DRAW);
    setVBO(textureCoords, 1, 2, GL_STATIC_DRAW);
    setVBO(normals, 2, 3, GL_STATIC_DRAW);
    setEBO(mesh.Indices, GL_STATIC_DRAW);
}
