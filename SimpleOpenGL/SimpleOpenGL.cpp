#include "SimpleOpenGL.h"
#include <glad/glad.h>
#include <stdio.h>

SimpleOpenGL::SimpleOpenGL()
{
    m_title = "Default title";
    m_size  = { 640, 480 };

    m_bVSync   = false;
    m_bRunning = false;
    m_bDrawFPS = false;
}

SimpleOpenGL::~SimpleOpenGL()
{
    m_window.close();
}

void SimpleOpenGL::setupWindow(sf::Vector2u size, std::string title)
{
    m_size  = size;
    m_title = title;
}

void SimpleOpenGL::start()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;    // Add this to make the depth buffer work
    settings.stencilBits = 8;

    m_window.create(sf::VideoMode(m_size.x, m_size.y), m_title, sf::Style::Default, settings);
    m_bRunning = true;

    // Load after window
    if (!gladLoadGL())
    {
        printf("Failed to gladLoadGL!");
        exit(-1);
    }
    else printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    // Main Event Loop 
    if (!OnUserCreate())
        m_bRunning = false;

    while (m_bRunning)
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_bRunning = false;
            if (event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
                m_bRunning = false;

            Event(event);
        }

        BeginDraw(0.2f, 0.3f, 0.3f, 1.0f);

        if (!OnUserUpdate(m_elapsed))
            m_bRunning = true;
        
        EndDraw();

        m_elapsed = m_clock.restart();

        if (m_bDrawFPS)
            m_window.setTitle(m_title + " - FPS: " + std::to_string(1.0f / m_elapsed.asSeconds()));
    }

}

int SimpleOpenGL::ScreenWidth()
{
    return m_size.x;
}

int SimpleOpenGL::ScreenHeight()
{
    return m_size.y;
}

void SimpleOpenGL::EnableVSync(bool vsync)
{
    m_bVSync = true;
    m_window.setVerticalSyncEnabled(m_bVSync);
}

bool SimpleOpenGL::IsVSyncOn()
{
    return m_bVSync;
}

void SimpleOpenGL::EnableFPSCounter(bool fps)
{
    m_bDrawFPS = fps;
}

void SimpleOpenGL::EnableWireframe(bool wireframe)
{
    if (wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else           glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

sf::Window * SimpleOpenGL::getWindow()
{
    return &m_window;
}

void SimpleOpenGL::Event(sf::Event & e)
{
}

void SimpleOpenGL::BeginDraw(float r, float g, float b, float a)
{
    // Enable the depth buffer
    glEnable(GL_DEPTH_TEST);

    // CLEAR DEPTH BUFFER BIT so triangles don't overlap
    // CLEAR COLOR BUFFER for background screen
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SimpleOpenGL::EndDraw()
{
    m_window.display();
}
