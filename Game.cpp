#include "Game.h"

#include "Scene.h"

void Game::update()
{
	scene->update();
}

std::shared_ptr<Game> getGame()
{
	static std::shared_ptr<Game> instance(nullptr);

	if (!instance)
	{
		instance = std::shared_ptr<Game>(new Game());
	}
	return instance;
}
