#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera()
    {
        m_position = glm::vec3(0, 0, 0);
        m_rotation = glm::vec3(0, 0, 0);
    }

    void Update(sf::Time elapsed, float Speed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m_position.z -= Speed * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m_position.z += Speed * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m_position.x += Speed * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            m_position.x -= Speed * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
            m_position.y -= Speed * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            m_position.y += Speed * elapsed.asSeconds();
        }
    }

    glm::vec3 getPosition() { return m_position; }
    glm::vec3 getRotation() { return m_rotation; }

private:
    glm::vec3 m_position;
    // Rotations are: Pitch, Yaw, Roll
    glm::vec3 m_rotation;
};

typedef std::unique_ptr<Camera> CameraRef;
