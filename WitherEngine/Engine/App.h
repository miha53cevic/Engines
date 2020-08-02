#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "../modules/states/StateMachine.h"

namespace we
{
    class App
    {
    public:
        App();

        void CreateWindow(int ScreenWidth, int ScreenHeight, std::string Title);
        void Run();

        int ScreenWidth();
        int ScreenHeight();

        sf::RenderWindow    &getWindow();
        StateMachine        &getStateMachine();

        void setVSync           (bool VSync);
        void setClearColour     (sf::Color c);

    private:
        bool m_isRunning;   
        bool m_VSync;

        sf::RenderWindow    m_window;
        sf::Vector2i        m_screenSize;
        sf::Color           m_clearColour;

        sf::Clock	m_clock;
        sf::Time	m_elapsed;

        StateMachine m_stateMachine;

        void CheckEvents();
        void ClearWindow();
        void DisplayWindow();
    };
}