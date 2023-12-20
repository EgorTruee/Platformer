#include "Game.h"

#include <SFML\Graphics\RenderTarget.hpp>

#include "Scene.h"
#include "PlayerController.h"

void Game::update()
{
	ticks.tick();

	scene->update();
	playerController->update();
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

void Game::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(*scene, state);
}

Game::Game() :
	playerController(getPlayerController())
{}
