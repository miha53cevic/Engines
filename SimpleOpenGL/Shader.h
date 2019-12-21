#pragma once
#include <string>
#include <GL/glew.h>

class Shader
{
public:
    Shader(const std::string& fileName);
    ~Shader();

    void Bind();

private:
    static const unsigned int NUM_SHADERS = 2;

    std::string LoadShader(const std::string& fileName);
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    GLuint CreateShader(const std::string& text, unsigned int type);

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
};