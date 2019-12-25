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
            // Calculate the directional vector and add it to camera position
            m_position.z -= Speed * elapsed.asSeconds() * cosf(glm::radians(-m_rotation.y));
            m_position.x -= Speed * elapsed.asSeconds() * sinf(glm::radians(-m_rotation.y));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m_position.z += Speed * elapsed.asSeconds() * cosf(glm::radians(-m_rotation.y));
            m_position.x += Speed * elapsed.asSeconds() * sinf(glm::radians(-m_rotation.y));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m_position.x += Speed * elapsed.asSeconds() * cosf(glm::radians(-m_rotation.y));
            m_position.z -= Speed * elapsed.asSeconds() * sinf(glm::radians(-m_rotation.y));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            m_position.x -= Speed * elapsed.asSeconds() * cosf(glm::radians(-m_rotation.y));
            m_position.z += Speed * elapsed.asSeconds() * sinf(glm::radians(-m_rotation.y));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
            m_position.y -= Speed * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            m_position.y += Speed * elapsed.asSeconds();
        }

        // Get the offset between mouse movements then add them to rotation
        const float sensetivity = 0.25f;

        sf::Vector2i mousePos = sf::Mouse::getPosition();
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            float xOffset = mousePos.x - lastPos.x;
            float yOffset = mousePos.y - lastPos.y;

            xOffset *= sensetivity;
            yOffset *= sensetivity;

            m_rotation.x += yOffset;
            m_rotation.y += xOffset;

            // Set max up/down rotation
            if (m_rotation.x > 90.0f)
                m_rotation.x = 90.0f;

            if (m_rotation.x < -90.0f)
                m_rotation.x = -90.0f;
        }

        lastPos = mousePos;
    }

    glm::vec3 getPosition() { return m_position; }
    glm::vec3 getRotation() { return m_rotation; }

private:
    glm::vec3 m_position;
    // Rotations are: Pitch, Yaw, Roll
    glm::vec3 m_rotation;

    sf::Vector2i lastPos;
};

typedef std::unique_ptr<Camera> CameraRef;
