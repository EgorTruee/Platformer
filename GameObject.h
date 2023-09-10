#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include <vector>

class GameObject
{
public:

	GameObject() {}
	GameObject(const GameObject&) = default;
	GameObject(GameObject&&) = default;

	virtual void start() = 0;
	virtual void update() = 0;
	virtual std::vector<const sf::Drawable*> getDrawable() = 0;

private:
};

