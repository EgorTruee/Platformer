#include "Game.h"

#include "GameObject.h"
#include "TestObject.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <iostream>

Game::Game() :
    paused(true)
{
    Game::createGameObject<TestObject>(sf::Vector2f(0, 0), sf::Vector2f(10, 10));
    Game::createGameObject<TestObject>(sf::Vector2f(100, 100), sf::Vector2f(0, 0));
    
}

void Game::start()
{
    clock.restart();

    t1 = clock.getElapsedTime();
    paused = false;
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
    
    updateObjects((t2 - t1).asSeconds());

    t1 = t2;
}

Game::~Game()
{
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& i : objects)
    {
        target.draw(*i, states);
    }
}

void Game::updateObjects(float dt)
{
    for (auto& object : objects)
    {
        object->update(dt);
    }
}


