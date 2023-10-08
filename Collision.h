#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>

class Collision : public sf::Transformable
{
public:

	explicit Collision(const std::vector<sf::Vector2f> vertex);
	explicit Collision(sf::Vector2f position = { 0, 0 }, 
		sf::Vector2f velocity = { 0, 0 },
		sf::Vector2f acceleration = { 0, 0 }, 
		const std::vector<sf::Vector2f> vertex = {});
	Collision(const Collision& other) = default;
	Collision(Collision&& other) = default;

	sf::FloatRect getBigRect() const;
	bool isInside(const sf::Vector2f& pos) const;
	bool isColiding(const Collision& other) const;

	std::vector<sf::Vector2f> getPoints() const;

	void setPoints(const std::vector<sf::Vector2f>& points);
	void setVelocity(sf::Vector2f Velocity);
	void setAcceleration(sf::Vector2f Acceleration);
	void update(float dt);

private:

	std::vector<sf::Vector2f> points;
	sf::Vector2f v = { 0, 0 };
	sf::Vector2f a = { 0, 0 };
};

