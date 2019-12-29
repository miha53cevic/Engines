#pragma once
#include "Math.h"
#include "Static_Shader.h"
#include "Entity.h"

class Renderer
{
public:
    Renderer(glm::vec2 screenSize)
    {
        m_FOV = 90;
        m_NEAR_PLANE = 0.1f;
        m_FAR_PLANE = 1000.0f;

        // Create projection Matrix
        m_projectionMatrix = Math::createProjectionMatrix(screenSize, m_FOV, m_NEAR_PLANE, m_FAR_PLANE);
    }

    void setFOV(float FOV)                  { m_FOV = FOV;                  }
    void setNEAR_PLANE(float NEAR_PLANE)    { m_NEAR_PLANE = NEAR_PLANE;    }
    void setFAR_PLANE(float FAR_PLANE)      { m_FAR_PLANE = FAR_PLANE;      }

    glm::mat4x4 getProjectionMatrix()       { return m_projectionMatrix;    }

    void Render(Entity* entity, Shader* shader)
    {
        // Don't draw faces that the camera can not see
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);

        glBindVertexArray(entity->getMesh()->VAO);

        glm::mat4x4 transformationMatrix = Math::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale());
        shader->loadTransformationMatrix(transformationMatrix);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, entity->getMesh()->TextureID);

        glDrawElements(GL_TRIANGLES, entity->getMesh()->getVertexCount(), GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
    }

private:
    float m_FOV;
    float m_NEAR_PLANE;
    float m_FAR_PLANE;

    glm::mat4x4 m_projectionMatrix;
};
