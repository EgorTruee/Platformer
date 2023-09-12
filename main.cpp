#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Fullscreen);
    sf::Vector2f pos(0, 0), vel(100, 100);
    sf::Clock clock;
    sf::Time t1, t2;
    Game game;

    game.start();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                window.close();
            }
        }
        t2 = t1;
        t1 = clock.getElapsedTime();

        game.update((t2 - t1).asSeconds());
        window.clear();

        for (auto drawable : game.getDrawable())
        {
            window.draw(*drawable);
        }
        window.display();
    }

    return 0;
}