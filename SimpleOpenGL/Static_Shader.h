#pragma once
#include "Shader.h"

class Static_Shader : public Shader
{
public:
    Static_Shader();
    ~Static_Shader();

private:
    void bindAttributes() override;
    void getAllUniformLocations() override;
};

