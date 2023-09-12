#include "Game.h"

#include <algorithm>

void Game::start()
{
    for (auto object : objects)
    {
        object->start();
    }
}

void Game::update(float delta)
{
    for (auto object : objects)
    {
        object->update(delta);
    }
}

std::vector<const sf::Drawable*> Game::getDrawable()
{
    std::vector<const sf::Drawable*> drawable;

    for (auto object : objects)
    {
        std::vector<const sf::Drawable*> t = object->getDrawable();

        std::copy(t.begin(), t.end(), drawable.end());
    }
    return drawable;
}

Game::~Game()
{
    for (auto object : objects)
    {
        delete object;
    }
}
