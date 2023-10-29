#pragma once

#include <SFML\Graphics\Drawable.hpp>

#include <memory>

class Scene;
class Game;

std::shared_ptr<Game> getGame();

class Game
{
public:

	friend std::shared_ptr<Game> getGame();

	void update();
	
	std::shared_ptr<Scene> getCurrentScene();

	void setScene(std::shared_ptr<Scene> newScene);

private:

	Game() {}
	Game(const Game& other) = delete;
	Game(Game&& other) = delete;

	std::shared_ptr<Scene> scene;
};

inline std::shared_ptr<Scene> Game::getCurrentScene()
{
	return scene;
}

inline void Game::setScene(std::shared_ptr<Scene> newScene)
{
	scene = newScene;
}
