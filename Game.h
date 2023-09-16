#pragma once

#include "GameObject.h"

#include <vector>
#include <utility>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class Game
{
public:

	Game();

	void start();
	void stop();
	void update();

	bool isPaused() { return paused; }
	std::vector<sf::Drawable*> getDrawable();

	template<class Object, typename... Args>
	void createGameObject(Args&... args);
	~Game();

private:

	std::vector<GameObject*> objects;
	sf::Time t1, t2;
	sf::Clock clock;
	bool paused;
};

template<class Object, typename... Args>
inline void Game::createGameObject(Args&... args)
{
	objects.push_back(new Object(std::forward<Args>(args)...));
}
