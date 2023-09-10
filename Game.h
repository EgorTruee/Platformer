#pragma once

#include "GameObject.h"

#include <vector>

#include <SFML/Graphics/Drawable.hpp>

class Game
{
public:

	Game() {}

	void start();
	void update();
	std::vector<const sf::Drawable*> getDrawable();

private:

	std::vector<GameObject*> objects;
};

