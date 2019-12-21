#include "Mesh.h"

Mesh::Mesh(const std::vector<GLfloat>& data, const std::vector<GLuint>& indicies)
{
    createVAO();
    bindIndiciesBuffer(indicies);
    storeDataInAttributeList(0, 3, data);
    unbindVAO();

    m_vertexCount = indicies.size();
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
}

void Mesh::Draw()
{
    // bind the VAO
    glBindVertexArray(m_VAO);

    glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, 0);

    unbindVAO();
}

void Mesh::operator=(Mesh & other)
{
    *this = other;
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
