#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader();
    ~Shader();

    void createProgram(const std::string& fileName);

    void Bind();
    void Unbind();


protected:
    virtual void bindAttributes() = 0;
    void bindAttribute(int attribute, std::string variableName);

    virtual void getAllUniformLocations() = 0;
    int getUniformLocation(std::string uniformName);

    void loadFloat(int location, float value);
    void loadVector(int location, glm::vec3 vector);
    void loadBool(int location, bool value);
    void loadMatrix(int location, const glm::mat4x4& matrix);

private:
    static const unsigned int NUM_SHADERS = 2;

    std::string LoadShader(const std::string& fileName);
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    GLuint CreateShader(const std::string& text, unsigned int type);

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];

public:
    void loadTransformationMatrix(glm::mat4x4 matrix);
    void loadProjectionMatrix(glm::mat4x4 matrix);

protected:
    int m_location_transMatrix;
    int m_location_projectMatrix;
    int m_location_viewMatrix;
};

typedef std::unique_ptr<Shader> ShaderRef;