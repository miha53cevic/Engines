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
}

void Static_Shader::getAllUniformLocations()
{
    //getUniformLocation();
}
