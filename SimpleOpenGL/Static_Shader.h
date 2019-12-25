#pragma once
#include "Shader.h"
#include "Light.h"

class Static_Shader : public Shader
{
public:
    Static_Shader() {}

    void loadLight(Light& light)
    {
        loadVector(m_location_lightPosition, light.getPosition());
        loadVector(m_location_lightColour, light.getColour());
    }

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

        m_location_lightPosition = getUniformLocation("lightPosition");
        m_location_lightColour = getUniformLocation("lightColour");
    }

private:
    int m_location_lightPosition;
    int m_location_lightColour;
};

typedef std::unique_ptr<Static_Shader> Static_ShaderRef;

