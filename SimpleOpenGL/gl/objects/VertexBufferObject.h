#pragma once
#include <glad/glad.h>
#include <vector>

namespace gl
{
    struct VertexBufferObject
    {
        VertexBufferObject();
        ~VertexBufferObject();

        GLuint VBO;

        void setData(std::vector<GLfloat> data, int attributeID, int size, int DrawingMode = GL_STATIC_DRAW);
    };
};
