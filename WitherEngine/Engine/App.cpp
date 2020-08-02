#include "App.h"
#include "../game_states/Playing.h"

we::App::App()
{
	m_VSync = true;

	m_clearColour = sf::Color(51, 51, 51);
}

void we::App::CreateWindow(int ScreenWidth, int ScreenHeight, std::string Title)
{
	m_window.create(sf::VideoMode(ScreenWidth, ScreenHeight), Title);

	if (m_VSync) m_window.setVerticalSyncEnabled(true);
	else         m_window.setVerticalSyncEnabled(false);

	m_screenSize = sf::Vector2i(ScreenWidth, ScreenHeight);
}

void we::App::Run()
{
	m_isRunning = true;

	// add starting state here
    m_stateMachine.AddState(std::make_unique<Playing>(this));
    m_stateMachine.ProcessStateChanges();

	while (m_isRunning)
	{
		CheckEvents();

		// Update state
		if (!m_stateMachine.isEmpty())
		{
			m_stateMachine.GetActiveState()->Update	(m_elapsed.asSeconds());
		}

		// Draw state
		ClearWindow();

		if (!m_stateMachine.isEmpty())
		{
			m_stateMachine.GetActiveState()->Draw(m_window);
		}

		DisplayWindow();

		// Get elapsed time / deltaTime
		m_elapsed = m_clock.restart();
	}
}

int we::App::ScreenWidth()                      { return m_screenSize.x; }
int we::App::ScreenHeight()                     { return m_screenSize.y; }

sf::RenderWindow &we::App::getWindow()          { return m_window; }
we::StateMachine &we::App::getStateMachine()    { return m_stateMachine; }

void we::App::setVSync(bool VSync)              { m_VSync = VSync;       }
void we::App::setClearColour(sf::Color c)       { m_clearColour = c;	 }

void we::App::CheckEvents()
{
	sf::Event e;
	while (m_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_isRunning = false;

		// Run state Events
		if (!m_stateMachine.isEmpty())
		{
			m_stateMachine.GetActiveState()->HandleInput(e);
		}
	}
}

void we::App::ClearWindow()     { m_window.clear(m_clearColour);    }
void we::App::DisplayWindow()   { m_window.display();               }
