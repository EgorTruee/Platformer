#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Fullscreen);
    sf::RectangleShape shape(sf::Vector2f(100.f, 100.f));
    sf::Vector2f pos(0, 0), vel(100, 100);
    sf::Clock clock;

    shape.setFillColor(sf::Color::Blue);

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
        if (pos.x > 1820 || pos.x < 0)
        {
            vel.x *= -1;
        }
        if (pos.y > 980 || pos.y < 0)
        {
            vel.y *= -1;
        }
        pos += vel * clock.getElapsedTime().asSeconds();
        
        clock.restart();
        shape.setPosition(pos);
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}