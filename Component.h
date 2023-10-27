#pragma once

#include <SFML\Graphics\Drawable.hpp>

class Component : public sf::Drawable
{
public:

	virtual void update(float dt) = 0;

	virtual ~Component() = default;
protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override = 0;
};

