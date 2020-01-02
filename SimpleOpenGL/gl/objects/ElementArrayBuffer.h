#pragma once
#include <glad/glad.h>

#include <vector>

namespace gl
{
    struct ElementArrayBuffer
    {
        ElementArrayBuffer();
        ~ElementArrayBuffer();

        void setData(std::vector<GLuint> indicies, int DrawMode = GL_STATIC_DRAW);

        GLuint EBO;
        GLuint size;
    };
};

