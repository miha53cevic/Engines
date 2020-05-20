#pragma once
#ifdef _WIN32
	#include <SDL.h>
#endif
#ifdef __linux__
	#include <SDL2/SDL.h>
#endif

#include <iostream>
#include <string>

/*-----------------------------------------------------------------------------*/

template<class T>
struct vec2
{
	vec2()
		: x(0)
		, y(0)
	{}

	vec2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	float magnitude()
	{
		return sqrtf(x*x + y*y);
	}

	vec2<T> unitVector()
	{
		float c = magnitude();
		return { x / c, y / c };
	}

	T x, y;
};

typedef vec2<int> ivec2;
typedef vec2<unsigned int> uvec2;
typedef vec2<float> fvec2;
typedef vec2<double> dvec2;

/*-----------------------------------------------------------------------------*/

class simpleSDL
{
public:
	simpleSDL()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cout << "Initialize error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}

		m_window   = nullptr;
		m_renderer = nullptr;
		m_bAlive   = false;
	}
	virtual ~simpleSDL()
	{
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);
		SDL_Quit();
	}

	void Construct(std::string title, unsigned int w, unsigned int h)
	{
		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
		if (m_window == nullptr)
		{
			std::cout << "Window creation error: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(m_window);
			SDL_Quit();
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (m_renderer == nullptr)
		{
			std::cout << "Render creation error: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(m_window);
			SDL_DestroyRenderer(m_renderer);
			SDL_Quit();
		}

		m_title = title;
		m_windowSize = uvec2(w, h);
		m_bAlive = true;
	}

protected:
	virtual void Event(const SDL_Event& e) {}
	virtual bool Setup() = 0;
	virtual bool Loop (float elapsed) = 0;

private:
	SDL_Window*   m_window;
	SDL_Renderer* m_renderer;

	std::string m_title;
	uvec2 		m_windowSize;

	bool 		m_bAlive;

protected:
	int ScreenWidth () { return m_windowSize.x; }
	int ScreenHeight() { return m_windowSize.y; }

	void Clear(int r = 0, int g = 0, int b = 0, int a = 255)
	{
		SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
		SDL_RenderClear(m_renderer);
	}

	void drawFillRect(int x, int y, int w, int h, SDL_Color c = { 255, 255, 255, 255 })
	{
		SDL_Rect rect = { x, y, w, h };
		SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
		SDL_RenderFillRect(m_renderer, &rect);
	}

	void drawRect(int x, int y, int w, int h, SDL_Color c = { 255, 255, 255, 255 })
	{
		SDL_Rect rect = { x, y, w, h };
		SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
		SDL_RenderDrawRect(m_renderer, &rect);
	}

	void drawLine(int x1, int y1, int x2, int y2, SDL_Color c = { 255, 255, 255, 255 })
	{
		SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
		SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
	}

	void drawPoint(int x, int y, SDL_Color c = { 255, 255, 255, 255 })
	{
		SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
		SDL_RenderDrawPoint(m_renderer, x, y);
	}

public:
	void Start()
	{
		if (m_window == nullptr && m_renderer == nullptr)
		{
			std::cout << "Start error: Construct() was never called!" << std::endl;
			return;
		}

		if (!Setup())
			m_bAlive = false;

		while (m_bAlive)
		{
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					m_bAlive = false;

				Event(e);
			}

			if (!Loop(0))
				m_bAlive = false;

			SDL_RenderPresent(m_renderer);
		}
	}
};

/*-----------------------------------------------------------------------------*/
