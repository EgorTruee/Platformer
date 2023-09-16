#include "Game.h"

#include "Moving.h"

#include <algorithm>
#include <iostream>

Game::Game() :
    paused(true)
{
}

void Game::start()
{
    clock.restart();

    t1 = clock.getElapsedTime();
    paused = false;

    createGameObject<Moving>();
}
void Game::stop()
{
    update();
    paused = true;
}
void Game::update()
{
    if (paused)
    {
        return;
    }
    t2 = clock.getElapsedTime();
    
    for (auto object : objects)
    {
        object->update((t2 - t1).asSeconds());
    }
    t1 = t2;
}

std::vector<sf::Drawable*> Game::getDrawable()
{
    std::vector<sf::Drawable*> drawable;

    for (auto object : objects)
    {
        std::vector<sf::Drawable*> t = object->getDrawable();

        for (auto i : t)
        {
            drawable.push_back(i);
        }
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
