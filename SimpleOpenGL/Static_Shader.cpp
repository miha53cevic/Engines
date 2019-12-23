#include "Static_Shader.h"

Static_Shader::Static_Shader()
{
}

Static_Shader::~Static_Shader()
{
}

void Static_Shader::bindAttributes()
{
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
}

void Static_Shader::getAllUniformLocations()
{
    m_location_transMatrix = getUniformLocation("transformationMatrix");
    m_location_projectMatrix = getUniformLocation("projectionMatrix");
    m_location_viewMatrix = getUniformLocation("viewMatrix");
}
