#include "Mesh.h"

#include <SFML/Graphics.hpp>

Mesh::Mesh(const std::vector<GLfloat>& data, const std::vector<GLuint>& indicies)
{
    createVAO();
    bindIndiciesBuffer(indicies);
    storeDataInAttributeList(0, 3, data);
    unbindVAO();

    m_vertexCount = indicies.size();

    // By default there is no texture
    m_TextureID = -1;
}

Mesh::~Mesh()
{
    // Free VAO
    glDeleteVertexArrays(1, &m_VAO);

    // Free VBOs
    for (auto& i : m_VBOs)
    {
        glDeleteBuffers(1, &i);
    }

    printf("Mesh: Destructor Called!\n");
}

void Mesh::Draw()
{
    // bind the VAO
    glBindVertexArray(m_VAO);

    // Check if a texture has been added
    if (m_TextureID != -1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, 0);

    unbindVAO();
}

void Mesh::addTexture(const std::string path, const std::vector<GLfloat>& textureCoords)
{
    glBindVertexArray(m_VAO);
    storeDataInAttributeList(1, 2, textureCoords);
    unbindVAO();

    loadTexture(path);
}

GLuint Mesh::getVAO()
{
    return m_VAO;
}

GLuint Mesh::getTexture()
{
    return m_TextureID;
}

int Mesh::getVertexCount()
{
    return m_vertexCount;
}

void Mesh::createVAO()  
{
    // Create a VertexArrayObject
    // a VAO contains all sorts of data that is stored in VBOs
    // Example: VAO contains
    // VertexData  stored in a VBO
    // IndicieData stored in a VBO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
}

void Mesh::unbindVAO()
{
    glBindVertexArray(0);
}

void Mesh::bindIndiciesBuffer(const std::vector<GLuint>& indicies)
{
    // Create a IndiciesBuffer which is a VBO
    // bind the buffer
    GLuint EBO;
    glGenBuffers(1, &EBO);

    // Store the VBO data for later cleanup
    m_VBOs.push_back(EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicies.size(), indicies.data(), GL_STATIC_DRAW);
}

void Mesh::storeDataInAttributeList(GLuint attributeID, GLuint size, const std::vector<GLfloat>& data)
{
    GLuint VBO;
    glGenBuffers(1, &VBO);

    // Store the VBO data for later cleanup
    m_VBOs.push_back(VBO);

    // Add data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);

    // AttributeLists are elements inside the VAO where we store VBOs like VAO[0] = VBO; the 0 is the AttributeList
    glVertexAttribPointer(attributeID, size, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attributeID);

    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::loadTexture(std::string fileName)
{
    sf::Image img;
    if (!img.loadFromFile(fileName))
    {
        // Error
        m_TextureID = -1;
    }
    else
    {
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        // Store for cleanup later
        m_textures.push_back(m_TextureID);

        // Send texture data to the GPU
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());

        // Must add these otherwise the texture doesn't load
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
}
