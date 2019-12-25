#pragma once
#include <glm/glm.hpp>

class Light
{
public:
    Light() {}
    Light(glm::vec3 pos, glm::vec3 colour)
    {
        m_position = pos;
        m_colour = colour;
    }

    void setPosition        (glm::vec3 pos)     { m_position = pos;     }
    void setColour          (glm::vec3 c)       { m_colour = c;         }

    glm::vec3 getPosition   ()                  { return m_position;    }
    glm::vec3 getColour     ()                  { return m_colour;      }

private:
    glm::vec3 m_position;
    glm::vec3 m_colour;
};