#pragma once
#include "GameObject.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Moving : public GameObject
{
public:

	Moving();

	virtual void update(float delta) override;
	virtual std::vector<sf::Drawable*> getDrawable() override;

	virtual ~Moving() override;

private:

	sf::RectangleShape* rect;
};

