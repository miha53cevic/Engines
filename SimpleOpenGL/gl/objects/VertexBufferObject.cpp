#include "VertexBufferObject.h"

gl::VertexBufferObject::VertexBufferObject()
{
    glGenBuffers(1, &VBO);
}

gl::VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &VBO);
}

void gl::VertexBufferObject::setData(std::vector<GLfloat> data, int attributeID, int size, int DrawingMode)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), DrawingMode);

    glEnableVertexAttribArray(attributeID);
    glVertexAttribPointer(attributeID, size, GL_FLOAT, false, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
