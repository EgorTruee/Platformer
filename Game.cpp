#include "Game.h"

#include "GameObject.h"
#include "Moving.h"
#include "Collision.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <iostream>

Game::Game() :
    paused(true)
{
    createGameObject<Moving>(Collision({ 0,0 }, { 10, 10 }, { 0, 0 }, 0, 0, { {10, 10}, {-10, 10}, {-10, -10}, {10, -10} }));
    createGameObject<Moving>(Collision({ 100, 100 }, { 0, 0 }, { 0, 0 }, 0, 0, { {10, 10}, {-10, 10}, {-10, -10}, {10, -10} }));
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
    updatePhysics((t2 - t1).asSeconds());

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

void Game::updatePhysics(float dt)
{
    for (auto& i : objects)
    {
        i->getCollision()->update(dt);
    }
    for (int i = 0; i < objects.size(); i++)
    {
        for (int j = i + 1; j < objects.size(); j++)
        {
            std::shared_ptr<Collision> collision1 = objects[i]->getCollision();
            std::shared_ptr<Collision> collision2 = objects[j]->getCollision();

            if (collision1->isColiding(*collision2))
            {
                collision1->collide(collision2);
                collision2->collide(collision1);
            }
        }
    }
}
