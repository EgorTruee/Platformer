#pragma once

#include "GameObject.h"

#include <vector>

#include <SFML/Graphics/Drawable.hpp>

class Game
{
public:

	Game() {}

	void start();
	void update(float delta);
	std::vector<const sf::Drawable*> getDrawable();

	template<class Object, typename... Args>
	void createGameObject(Args&... args);
	~Game();

private:

	std::vector<GameObject*> objects;
};

template<class Object, typename... Args>
inline void Game::createGameObject(Args&... args)
{
	objects.push_back(new Object(std::forward<Args>(args)...);
}
