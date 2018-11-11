#include <iostream>

#include "mihaSimpleSFML.h"

class demo : public mihaSimpleSFML
{
public:
	demo() {}

private:
	sf::RectangleShape shape;

protected:
	virtual bool OnUserCreate()
	{
		shape.setSize({100,100});
		shape.setOrigin(50, 50);
		shape.setPosition(sf::Vector2f(ScreenWidth() / 2, ScreenHeight() / 2));

		return true;
	}

	virtual bool OnUserUpdate(sf::Time elapsed)
	{
		Draw(shape);

		return true;
	}

};

int main()
{
	demo Test;
	Test.Construct(1280, 720, L"demo app");
	Test.Start();

	return 0;
}
