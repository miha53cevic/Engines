#pragma once
#include <SFML/Window.hpp>
#include <string>

class SimpleOpenGL
{
public:
    SimpleOpenGL();
    ~SimpleOpenGL();

    void setupWindow(sf::Vector2u size, std::string title);
    void start();

    int ScreenWidth();
    int ScreenHeight();

    void EnableVSync(bool vsync);
    bool IsVSyncOn();

    void EnableFPSCounter(bool fps);

    sf::Window* getWindow();

protected:
    virtual void Event(sf::Event& e);
    virtual bool OnUserCreate() = 0;
    virtual bool OnUserUpdate(sf::Time elapsed) = 0;

private:
    sf::Window   m_window;
    sf::Vector2u m_size;
    std::string  m_title;

    bool m_bRunning;
    bool m_bVSync;
    bool m_bDrawFPS;

    sf::Clock m_clock;
    sf::Time  m_elapsed;

    void BeginDraw(float r, float g, float b, float a);
    void EndDraw();
};

