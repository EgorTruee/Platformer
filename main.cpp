#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Scene.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "Platformer"/*, sf::Style::Fullscreen */ );
    sf::Vector2f pos(0, 0), vel(100, 100);
    std::shared_ptr<Game> game = getGame();

    game->setScene(std::make_shared<Scene>());
    game->getCurrentScene()->start();

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
        game->update();
        window.clear();
        window.draw(*game);
        window.display();
    }

    return 0;
}