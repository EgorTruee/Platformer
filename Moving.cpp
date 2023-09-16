#include "Moving.h"

Moving::Moving() :
	rect(nullptr)
{
	rect = new sf::RectangleShape(sf::Vector2f(100, 100));
	pos = sf::Vector2f(100, 100);
}

void Moving::update(float delta)
{
	pos += sf::Vector2f(100, 100) * delta;

	rect->setPosition(pos);
}

std::vector<sf::Drawable*> Moving::getDrawable()
{
	return std::vector<sf::Drawable*>({rect});
}

Moving::~Moving()
{
	if (rect)
	{
		delete rect;
	}
}
