#include "shader.h"
#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader()
{ 
}

Shader::~Shader()
{
    for (unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}

void Shader::createProgram(const std::string & fileName)
{
    m_program = glCreateProgram();
    m_shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

    for (unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);


    bindAttributes();

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

    getAllUniformLocations();
}

void Shader::Bind()
{
    glUseProgram(m_program);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

std::string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if (file.is_open())
    {
        while (file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE)
    {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
    GLuint shader = glCreateShader(type);

    if (shader == 0)
        std::cerr << "Error compiling shader type " << type << std::endl;

    const GLchar* p[1];
    p[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = text.length();

    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

    return shader;
}

void Shader::bindAttribute(int attribute, std::string variableName)
{
    glBindAttribLocation(m_program, attribute, variableName.c_str());
}

int Shader::getUniformLocation(std::string uniformName)
{
    return glGetUniformLocation(m_program, uniformName.c_str());
}

void Shader::loadFloat(int location, float value)
{
    glUniform1f(location, value);
}

void Shader::loadVector(int location, glm::vec3 vector)
{
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::loadBool(int location, bool value)
{
    float out = 0.0f;
    if (value)
        out = 1.0f;

    glUniform1f(location, value);
}

void Shader::loadMatrix(int location, const glm::mat4x4 & matrix)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::loadTransformationMatrix(glm::mat4x4 matrix)
{
    loadMatrix(m_location_transMatrix, matrix);
}

void Shader::loadProjectionMatrix(glm::mat4x4 matrix)
{
    Bind();
    loadMatrix(m_location_projectMatrix, matrix);
    Unbind();
}

void Shader::loadViewMatrix(Camera* camera)
{
    glm::mat4x4 viewMatrix = Math::createViewMatrix(camera);

    loadMatrix(m_location_viewMatrix, viewMatrix);
}
