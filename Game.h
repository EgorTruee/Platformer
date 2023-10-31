#pragma once

#include <SFML\Graphics\Drawable.hpp>

#include <memory>

#include "Ticker.h"

class Scene;
class Game;

std::shared_ptr<Game> getGame();

class Game : public sf::Drawable
{
public:

	friend std::shared_ptr<Game> getGame();

	void update();
	
	std::shared_ptr<Scene> getCurrentScene();
	sf::Time getTimePerTick();
	float getTPS();

	void setScene(std::shared_ptr<Scene> newScene);

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

private:

	Game() {}
	Game(const Game& other) = delete;
	Game(Game&& other) = delete;

	std::shared_ptr<Scene> scene;
	Ticker ticks;
};

inline std::shared_ptr<Scene> Game::getCurrentScene()
{
	return scene;
}

inline sf::Time Game::getTimePerTick()
{
	return ticks.getTimePerTick();
}

inline float Game::getTPS()
{
	return ticks.getTicksPerSecond();
}

inline void Game::setScene(std::shared_ptr<Scene> newScene)
{
	scene = newScene;
}
