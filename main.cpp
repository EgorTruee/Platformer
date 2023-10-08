#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "Platformer"/*, sf::Style::Fullscreen */ );
    sf::Vector2f pos(0, 0), vel(100, 100);
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
                if (event.key.scancode == sf::Keyboard::Scan::Space)
                {
                    if (game.isPaused())
                    {
                        game.start();
                    }
                    else
                    {
                        game.stop();
                    }
                }
                else
                {
                    window.close();
                }
            }
        }
        game.update();
        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}