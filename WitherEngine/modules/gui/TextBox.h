#pragma once
#include "../resource/ResourceManager.h"

namespace we
{
    class App;

    class TextBox
    {
    public:
        TextBox(App* app);
        
        void Draw                   (sf::RenderWindow &window);

        void setString              (std::string String);
        void setCharachterSize      (int size);
        void setFillColour          (sf::Color c);
        void setOutlinecolour       (sf::Color c);
        void setOutlineThickness    (int thickness);
        void setPosition            (float x, float y);
        
        bool MouseHover             ();

        sf::Text &getText           ();

        void centerText();

    private:
        sf::Text    m_text;
        App*        m_app;
    };
}
