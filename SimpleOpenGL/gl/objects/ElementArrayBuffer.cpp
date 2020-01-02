#include "ElementArrayBuffer.h"

gl::ElementArrayBuffer::ElementArrayBuffer()
{
}

gl::ElementArrayBuffer::~ElementArrayBuffer()
{
    glDeleteBuffers(1, &EBO);
}

void gl::ElementArrayBuffer::setData(std::vector<GLuint> indicies, int DrawMode)
{
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicies.size(), indicies.data(), DrawMode);

    size = indicies.size();
}
