#include "simpleSFML.h"

class demo : public ssf::simpleSFML
{
public:
	demo() {}

private:

protected:
    void Event(sf::Event e) override
    {
    }

protected:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(sf::Time elapsed) override
	{
		ClearDraw(sf::Color::Black);
		return true;
	}

};

int main()
{
	demo app;
	app.Construct(640, 480, L"demo app");
	app.Start();

	return 0;
}
