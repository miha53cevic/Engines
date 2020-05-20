#include "simpleSDL.h"

class demo : public simpleSDL
{
public:
	demo() {}

private:
	virtual void Event(const SDL_Event &e)
	{}

	virtual bool Setup()
	{
		return true;
	}

	virtual bool Loop(float elapsed)
	{
		Clear();
		drawRect(ScreenWidth() / 2 - 100, ScreenHeight() / 2 - 100, 200, 200);
		return true;
	}
};

int main(int argc, char* argv[])
{
	demo app;
	app.Construct("Demo app", 1280, 720);
	app.Start();
	return 0;
}
