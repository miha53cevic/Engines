#pragma once
#include "Shader.h"

class Static_Shader : public Shader
{
public:
    Static_Shader() {}

private:
    void bindAttributes() override
    {
        bindAttribute(0, "position");
        bindAttribute(1, "textureCoords");
        bindAttribute(2, "normal");
    }

    void getAllUniformLocations() override
    {
        m_location_transMatrix = getUniformLocation("transformationMatrix");
        m_location_projectMatrix = getUniformLocation("projectionMatrix");
        m_location_viewMatrix = getUniformLocation("viewMatrix");
    }

private:
};

