#pragma once
#include <SFML/Graphics.hpp>

namespace we
{
	class App;
	
	class State
	{
	public:
		State(App* app)
			: m_app(app)
		{}

		virtual void Init()                             = 0;

		virtual void HandleInput(sf::Event& e)          = 0;
		virtual void Update(float deltaTime)            = 0;
		virtual void Draw(sf::RenderWindow& window)     = 0;

		virtual void Pause()	{}
		virtual void Resume()	{}

	protected:
		App* m_app;
	};
}
