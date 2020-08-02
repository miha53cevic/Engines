#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace we
{
    class ResourceManager
    {
    public:
        ResourceManager()
        {
            // Try to load textures
            std::ifstream config;
            config.open("dependencies/textures.cfg");

            if (config.fail())
                std::cout << "Could not open textures.cfg\n";
            else
            {
                std::string name, path;
                while (!config.eof())
                {
                    config >> name >> path;

                    sf::Texture texture;
                    if (!texture.loadFromFile(path))
                    {
                        // Error
                    }
                    else
                    {
                        // Add texture to the map at the key name
                        m_textures[name] = texture;
                    }
                }
            }

            std::cout << "Loaded " << m_textures.size() << " texture(s)\n";

            // Load font
            if (!m_font.loadFromFile("dependencies/fonts/arial.ttf"))
            {
                // Error
            }
            else std::cout << "Loaded font arial.ttf\n";

            // Close file
            config.close();
        }

        // static functions -> can be called with sResourceManager::get()
        // Creates a single instance of the class thanks to static
        static ResourceManager &get()
        {
            static ResourceManager manager;
            return manager;
        }

        // Check if a texture exists
        // Send back that texture if it does
        // If it doesn't send back error texture
        sf::Texture &getTexture(std::string name)
        {
            if (m_textures.find(name) != m_textures.end())
            {
                return m_textures.at(name);
            }
            else return m_textures.at("error");
        }

        // Get font
        sf::Font &getFont() { return m_font; }

    private:
        std::map<std::string, sf::Texture> m_textures;

        sf::Font m_font;
    };
}
